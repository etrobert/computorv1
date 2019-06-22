NAME				=	computor

COLOR				=	\033[32m
COLOR_RESET	=	\033[0m

SRCDIR			=	.
OBJDIR			=	objs
INCDIR			=	includes

SRCNAM			=	main.cpp computorv1.cpp split_string.cpp smath.cpp
INCNAM			=

CC					=	g++
CFLAGS			=	-Wall -Wextra -Werror -I$(INCDIR) -std=c++1z
LDFLAGS			=	

GIT					=	README.md

SRC					=	$(SRCNAM:%=$(SRCDIR)/%)
INC					=	$(INCNAM:%=$(INCDIR)/%)
OBJ					=	$(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

.PHONY: all git clean fclean re tags

all:
	@$(MAKE) $(NAME)

$(OBJDIR)/computorv1.o: Polynomial.h

$(NAME): $(OBJ)
	@printf "%-15s%s\n" Linking $@
	@$(CC) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INC)
	@printf "%-15s%s\n" Compiling $@ 
	@mkdir -p $(OBJDIR)
	@$(CC) -o $@ -c $< $(CFLAGS)

git:
	@echo "Adding files to git repository"
	git add $(SRC) $(INC) $(GIT)

tags:
	@echo "Generating tags"
	@ctags -R --sort=yes --c++-kinds=+p --fields=+iaS --extra=+q .

clean:
	@echo "Suppressing obj files"
	@rm -rf $(OBJDIR)

fclean: clean
	@echo "Suppressing $(NAME)"
	@rm -rf $(NAME)

# $(MAKE) needed so that the cleaning is done before starting to create again \
	# cf make -j 
re: fclean
	@$(MAKE) all
