NAME				=	exec

COLOR				=	\033[32m
COLOR_RESET	=	\033[0m

SRCDIR			=	.
OBJDIR			=	objs
INCDIR			=	includes

SRCNAM			=	main.cpp computorv1.cpp split_string.cpp
INCNAM			=

CC					=	g++
CFLAGS			=	-Wall -Wextra -Werror -I$(INCDIR)
LDFLAGS			=	

GIT					=	README.md

SRC					=	$(SRCNAM:%=$(SRCDIR)/%)
INC					=	$(INCNAM:%=$(INCDIR)/%)
OBJ					=	$(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

.PHONY: all git clean fclean re tags

all:
	@$(MAKE) $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) printname
	@printf "%-15s%s\n" Linking $@
	@$(CC) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INC)
	@$(MAKE) printname
	@printf "%-15s%s\n" Compiling $@ 
	@mkdir -p $(OBJDIR)
	@$(CC) -o $@ -c $< $(CFLAGS)

git:
	@$(MAKE) printname
	@echo "Adding files to git repository"
	git add $(SRC) $(INC) $(GIT)

tags:
	@$(MAKE) printname
	@echo "Generating tags"
	@ctags -R --sort=yes --c++-kinds=+p --fields=+iaS --extra=+q .

printname:
	@printf "$(COLOR)"
	@printf "[%-15s " "$(NAME)]"
	@printf "$(COLOR_RESET)"

clean:
	@$(MAKE) printname
	@echo "Suppressing obj files"
	@rm -rf $(OBJDIR)

fclean: clean
	@$(MAKE) printname
	@echo "Suppressing $(NAME)"
	@rm -rf $(NAME)

# $(MAKE) needed so that the cleaning is done before starting to create again \
	# cf make -j 
re: fclean
	@$(MAKE) all
