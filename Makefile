######################################################################
######################################################################
#                             VARIABLES
######################################################################
######################################################################


MAKEFILE := $(abspath $(lastword $(MAKEFILE_LIST)))

include make-lib/dirmathq.mk
include $(DIR_MATHQ)/make-lib/variables.mk
include $(DIR_MATHQ)/make-lib/style.mk
include $(DIR_MATHQ)/make-lib/doc.mk

MAKEFILE_REL := $(subst $(DIR_MATHQ)/,,$(MAKEFILE))


# dynamic variables
RUN_FILES = $(wildcard */run)
RUN_SUBDIRS = $(dir $(RUN_FILES))
RUN_TARGETS = $(addprefix run_,$(RUN_SUBDIRS))


#---------------------------------------------------------------------
#---------------------------------------------------------------------
#                              RECIPES
#---------------------------------------------------------------------
#---------------------------------------------------------------------


#---------------------------------------------------------------------
#  SPECIAL RECIPES -- THESE MUST BE FIRST
#---------------------------------------------------------------------

# force these to always run regardless if prereq's are older or newer
.PHONY: run gitignore

# Each Makefile that has an include statement for this file should define a target "some" that makes all targets in that directory but not in subdirectories
default: all

#prevent any default rules from being used
.SUFFIXES:

# don't delete these files after compilation
.PRECIOUS: 

FORCE: ;


#  Do NOT include $(DIR_MATHQ)/make-lib/recipes.mk because 
#  we define recipes with the same name below and having both
#  is problematic

include $(DIR_MATHQ)/make-lib/info.mk


#---------------------------------------------------------------------
# build recipes
#---------------------------------------------------------------------
newrev: FORCE
	\python3 $(DIR_MATHQ)/scripts/createrev.py $(COMPATIBLE_VERSION_MATHQ_FILE) $(TAG_FILE_MATHQ) $(TAG_ANNOTATION_FILE)
	@chmod a-w $(TAG_FILE_MATHQ) 
	@chmod a-w $(TAG_ANNOTATION_FILE)

$(TAG_FILE_MATHQ): $(COMPATIBLE_VERSION_MATHQ_FILE)
	newrev

versioning: newrev

includes: FORCE
	make -C $(DIR_MATHQ)/include -j all
#	\cd $(DIR_MATHQ)/include && make -j all

src: FORCE
	\cd $(DIR_MATHQ)/src && make -j all

example: FORCE
	\cd $(DIR_MATHQ)/examples && make -j all 

test: FORCE
	\cd $(DIR_MATHQ)/test && make -j all 

benchmark: FORCE
	\cd $(DIR_MATHQ)/benchmark && make -j all 

doc: FORCE
	\cd $(DIR_MATHQ)/doc && make -j all 

sandbox: FORCE
	\cd $(DIR_MATHQ)/sandbox && make -j all 

README.md: $(CREATE_TOP) $(TAG_FILE_MATHQ) template.md
	python3 $(CREATE_TOP) $(TAG_FILE_MATHQ) template.md
	@chmod a-w README.md

some: README.md

all: versioning includes src example benchmark test sandbox README.md #doc

run_%: FORCE
	cd $* && ./run

run: $(RUN_TARGETS)
	@echo -e ${BOLD}${GREEN}"All executables in all subdirectories PASSED"${DEFCLR}${NORMAL}
#	@echo " RUN_FILES=$(RUN_FILES)"
	@echo " RUN_SUBDIRS=$(RUN_SUBDIRS)"
#	@echo " RUN_TARGETS=$(RUN_TARGETS)"

#---------------------------------------------------------------------
# cleaning recipes
#---------------------------------------------------------------------

# clean in reverse order
clean: 
#	\cd $(DIR_MATHQ)/doc && make -j clean 
	rm -f README.md
	\cd $(DIR_MATHQ)/sandbox && make -j clean
	\cd $(DIR_MATHQ)/test && make -j clean
	\cd $(DIR_MATHQ)/benchmark && make -j clean
	\cd $(DIR_MATHQ)/examples && make -j clean
	\cd $(DIR_MATHQ)/src && make -j clean
	\cd $(DIR_MATHQ)/include && make -j clean 

# clean in reverse order
cleanall: 
	\cd $(DIR_MATHQ)/sandbox && make -j clean
	\cd $(DIR_MATHQ)/test && make -j cleanall
	\cd $(DIR_MATHQ)/benchmark && make -j cleanall
	\cd $(DIR_MATHQ)/examples && make -j cleanall
	\cd $(DIR_MATHQ)/src && make -j cleanall
	\cd $(DIR_MATHQ)/include && make -j cleanall
	\rm -f $(TAG_FILE_MATHQ) 
	git restore $(TAG_FILE_MATHQ) 
	\rm -f $(TAG_ANNOTATION_FILE)
	git restore $(TAG_ANNOTATION_FILE) 


#---------------------------------------------------------------------
# git related recipes
#---------------------------------------------------------------------

pull:
	git pull origin master


.ONESHELL:
git: newrev
	@echo
	@git remote update origin
	@if [[ $$(git fetch --dry-run) ]]
	@then 
	@  echo "Your local repo is NOT up-to-date: execute 'git pull' first"
	@  exit
	@else 
	@  echo "Your local repo is up-to-date"
	@fi
	@git add $(TAG_FILE_MATHQ) $(TAG_ANNOTATION_FILE)
	@git add $(VERSION_HEADER_FILE_MATHQ)
	@echo
	@git status 
	@echo 
	@echo "THE FOLLOWING COMMANDS WILL BE EXECUTED:"
	@echo -e "git commit"
# need to be really careful with how we use colro and bold here to get it to work	
	@echo -e "git tag --file=$(TAG_ANNOTATION_FILE) --cleanup verbatim "$(BLUE)$(BOLD)`cat $(TAG_FILE_MATHQ)`$(DEFCLR)$(NORMAL)
	@echo -e "git push --tags origin "$(BLUE)$(BOLD)`git branch --show-current`$(DEFCLR)$(NORMAL)
	@
	@prompt="Would you like to commit these changes and push to githib [y/N]? "
	@read -r -p "$${prompt}" response
	@response=$${response,,}
	@if [[ ! $${response} =~ ^(y|Y|yes|YES)$$ ]]
	@then
	@  echo "Exiting with no action taken"
	@else
	@  echo "Commit, tag, and push to commit..."
	  git commit
	  git tag --file=$(TAG_ANNOTATION_FILE) --cleanup verbatim `cat $(TAG_FILE_MATHQ)`
	  git push --tags origin `git branch --show-current` 
	@fi


gitall: all git



#---------------------------------------------------------------------
# HELP recipes
#---------------------------------------------------------------------

define HELP
#############################################################################
#   Mathématiques $(shell cat $(TAG_FILE_MATHQ)) Top-Level Makefile
#
#   Note: You must execute './configure' before running this Makefile.
#         Execute './reconfigure' to re-perform the configuration.
##############################################################################
#
# make help
#      This help screen.
# make all
#      Recursively build the entire library, including documentation
# make run
#      Execute all executables in the subdirectories.  
#      This is a first-order test of the build.
#      This command terminates immediately if an error occurs.
# make info
#      Prints summary of all the make variables.
# make clean
#      Clean most of the files in this directory and all subdirectories
# make cleanall
#      Clean all of the files created by 'make all'.
#      Files created by './configure' are not removed.  
#      Execute './deconfigure' to remove all artefacts. 
# make git
#      Commits staged changes to the repo, creates a version tag and 
#      pushes to github.  Don't worry: YOU ARE PROMPTED BEFORE it actually
#      executes any git commands.
###############################################################################
endef
export HELP

help:
	@echo "$${HELP}"
