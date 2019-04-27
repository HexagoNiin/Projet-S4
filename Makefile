# PARAMÈTRES COMPILATEUR
CC=gcc
OPT=-Wall -g

# RÉPERTOIRES
HEADDIR=headers
SRCDIR=src
TESTSDIR=tests

# DÉPENDENCES
DISK=utils_virtual_disk.o
BLOCK=utils_block.o $(DISK)
STRIPE=utils_stripe.o $(BLOCK)
INODE=utils_inode.o $(STRIPE)
FILE=utils_file.o $(INODE)
OS=utils_os.o $(FILE)

# AFFICHAGE DEBUG
ifeq ($(log),1)
OPT+=-D _LOG1
endif
ifeq ($(log),2)
OPT+=-D _LOG2
endif
ifeq ($(log),3)
OPT+=-D _LOG3
endif
ifeq ($(log),4)
OPT+=-D _LOG4
endif
ifeq ($(log),5)
OPT+=-D _LOG5
endif
ifeq ($(log),6)
OPT+=-D _LOG6
endif

# PROGRAMMES
cmd_test: cmd_test.o $(STRIPE)
	$(CC) -o $@ $^ $(OPT)
	mv $@ $@.out

cmd_inode: cmd_inode.o $(INODE)
	$(CC) -o $@ $^ $(OPT)
	mv $@ $@.out

cmd_file: cmd_file.o $(FILE)
	$(CC) -o $@ $^ $(OPT)
	mv $@ $@.out

cmd_format: cmd_format.o
	$(CC) -o $@ $^ $(OPT)
	mv $@ $@.out

# AUTOMATISATION
%.o: $(SRCDIR)/%.c
	$(CC) -o $@ -c $< $(OPT)

# NETTOYAGE
clean:
	rm -rf *.o *.exe *.stackdump



# EXPLICATIONS SUR LE MAKEFILE

# Toutes les variables ne sont pas forcément utiles, mais sont là histoire de
# les avoir si nécessaire.
#
# Tel qu'est définie l'automatisation pour la compilation des fichiers objets
# (.o), il est nécessaire que tous les fichiers .c soient dans le répertoire
# "src". Cette cible est très importante et ne doit en aucun cas disparaître.
#
# Les dépendences sont définies "récursivement" et permettent d'inclure tous Les
# fichiers objets nécessaires antérieurs à celui correspondant au nom de la
# variable.
#
# Il devrait normalement suffire d'imiter les premières cibles écrites par mes
# soins pour ajouter la votre au makefile. Il y aurait donc deux commandes par
# cible.
#
# la commande "mv $@ $@.out" sert à mettre automatiquement l'extension .out au
# fichier généré, afin notamment de ne pas l'uploader sur github (les .out sont
# automatiquement ignorés) ; car il ne sert et serait redondant de posséder des
# fichiers que nous pouvons générer avec le reste.
#
# Pour afficher des infos de debug (avec la "fonction" debug(x) dans le
# programme), il suffit de donner une valeur quelconque au paramètre DEBUG en
# appelant le make
# Exemple : make cmd_file DEBUG=yes
