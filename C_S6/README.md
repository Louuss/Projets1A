# CASCASONNE PROJECT

## How to use it

First, note that your clients should be buils as dynamic libraries --> .so

The main make rules to use the project are:

-   build: Builds the project
-   test: Launches all the tests
-   install: Builds all the client's libraries and the server in the install folder
-   clean: Deletes all the .o, .so files

You can launch manually the game by using a command from the root folder:

./install/server ./install/client_0.so ./install/client_1.so

## Organisation of the project

The root folder contains the following folders

-   doc: for the documentation, using doxyfile
-   install: contains all the .so of the clients and the executable of the server after tou build the project
-   PROJET_des_autres_groupes: stores the .so of the other groups for testing purpose
-   SauvegardesMakefile: stores the old Makefiles
-   src: Contains the sources of the project
    -   clients: contains the sources of the project
-   tst: contains the tests
