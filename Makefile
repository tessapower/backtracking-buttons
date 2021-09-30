# ------------------------------------------------------------------------------------------------------ Make Config --#

MAKEFLAGS += --warn-undefined-variables
.DEFAULT_GOAL := help

# -------------------------------------------------------------------------------------------------------- Constants --#

SUB_NUM ?= 3 ## Assignment number which appears at the top of main.cpp
SUBMISSION_DIR = ./dist/sub
SOURCES = $(wildcard ./src/*.cpp)
HEADERS = $(wildcard ./include/*.h)

# --------------------------------------------------------------------------------------------------- Public Targets --#

.PHONY: help
help: MAKEFILE_FMT = "  \033[36m%-25s\033[0m%s\n"
help: ## (default) Displays this message
	@echo "Targets:"
	@grep -E '^[a-zA-Z0-9_-]+:.*?##' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?##"}; {printf $(MAKEFILE_FMT), $$1, $$2}'
	@echo ""
	@echo "Parameters:"
	@grep -E '^[A-Z0-9_]+ ?\?=.*?##' $(MAKEFILE_LIST) | awk 'BEGIN {FS = " ?\\?=.*?##"}; {printf $(MAKEFILE_FMT), $$1, $$2}'

.PHONY: test
test: build ## Build GoogleTest and run tests
	@clang++ \
			-std=c++17 \
			-fcolor-diagnostics \
			-pthread \
			-lgtest_main \
			-lgtest \
			-Iinclude \
			-o ./dist/main_tests \
			./tests/*.cpp ./src/*.cpp \
			2>&1 \
		&& ./dist/main_tests \
			--gtest_color=yes

.PHONY: test_scripts
test_scripts: build_argv ## Load and execute all text-based scripts
	for file in tests/*.txt; do \
		echo "Running test $${file}...\n"; \
		./dist/argv_main "$${file}"; \
		echo "\n"; \
	done

.PHONY: build_argv
build_argv: dist/argv_main ## Build the argv version of the program

.PHONY: build
build: dist/main ## Build the program

.PHONY: sub
sub: dist _fake_sysinclude  ## Create a submittable assignment
	@mkdir -p $(SUBMISSION_DIR)

	@# Create submission header
	@echo '// Tessa Power 14112766' > $(SUBMISSION_DIR)/main.cpp
	@echo '// Assignment $(SUB_NUM)' >> $(SUBMISSION_DIR)/main.cpp
	@echo '' >> $(SUBMISSION_DIR)/main.cpp

	@# Add all system includes, sorted with duplicates removed, to the top of the submission
	@cat \
			./bin/main.cpp ./src/* ./include/* \
		| egrep '^#include <' \
		| sort \
		| uniq \
		>> $(SUBMISSION_DIR)/main.cpp

	@# Copies contents of header files into submission
	@cat \
			./bin/main.cpp ./src/* \
		| egrep -o '^#include ".*' \
		| sort \
		| uniq \
		| sed -E 's;^#include "(.+)";include/\1;' \
		| xargs cat \
		| egrep -v '^#ifndef ([A-Z_]+)?_H' \
		| egrep -v '^#define ([A-Z_]+)?_H' \
		| egrep -v '^#endif // ([A-Z_]+)?_H' \
		| egrep -v '^#include <.*' \
		| cat -s - \
		>> $(SUBMISSION_DIR)/main.cpp

	@# Append all source files with #include statements removed
	@cat \
			./bin/main.cpp ./src/* \
		| grep -Ev '^#include.*' \
		| cat -s - \
		>> $(SUBMISSION_DIR)/main.cpp

	@# Always add new line to end of submission
	@echo '' >> $(SUBMISSION_DIR)/main.cpp

	@# Build to make sure it worked
	@clang++ -std=c++17 -o $(SUBMISSION_DIR)/main $(SUBMISSION_DIR)/main.cpp

.PHONY: run
run: build ## Build and run the program
	@cd ./dist && ./main

.PHONY: lint
lint: ## Run only the linter
	@clang-tidy \
		-header-filter=./include/* \
		--warnings-as-errors='*' \
		./src/*.cpp ./include/* ./bin/main.cpp \
		-- \
		-x c++ \
		-Iinclude \
		2> /dev/null

.PHONY: watch
watch: ## Hot load changes and run tests
	@find \( -name '*.cpp' -o -name '*.h' \) -print \
	| entr make test

.PHONY: clean
clean: ## Remove generated files
	@rm -rf ./dist 2> /dev/null || true


# -------------------------------------------------------------------------------------------------- Private Targets --#

dist:
	@mkdir $@

dist/argv_main: dist ./bin/argv_main.cpp $(SOURCES) $(HEADERS)
	clang++ -std=c++17 -g -Iinclude -o ./dist/$(@F) ./bin/$(@F).cpp $(SOURCES)

dist/main: dist ./bin/main.cpp $(SOURCES) $(HEADERS)
	clang++ -std=c++17 -g -Iinclude -o ./dist/$(@F) ./bin/$(@F).cpp $(SOURCES)

.PHONY: _fake_sysinclude
_fake_sysinclude: dist
	@mkdir -p ./dist/sysinclude 2> /dev/null || true
	@cat \
			./bin/main.cpp ./src/* ./include/* \
		| egrep '^#include <' \
		| sort \
		| uniq \
		| sed -E 's/^#include <(.+)>/\1/' \
		| xargs \
			-I'{}' \
			touch ./dist/sysinclude/'{}'
