# Compiler
CC = g++

# Compilation type
DEBUG = -g
RELEASE = -g
PRODUCTION = -g

# Compiler flags
DEBUGFLAGS = -g
RELEASEFLAGS =
PRODUCTIONFLAGS =
WARNSFLAGS = -W -Wall
CFLAGS = -std=c++11 $(DEBUGFLAGS) $(WARNSFLAGS)

# Paths
MAINPATH = ..
GTEST_PATH = $(MAINPATH)/linux/gtest-1.7.0
TESTS_PATH = $(MAINPATH)/src/gtests

# Includes' path
IUPINCLUDES = -I$(MAINPATH)/3rd_party_libs/iup/iup-3.10.1_Linux35_64_lib/include
WNDINCLUDES = -I$(MAINPATH)/src/application/gui
GENINCLUDES = -I$(MAINPATH)/include -I$(MAINPATH)/include/opengl
INCLUDES = $(IUPINCLUDES) $(WNDINCLUDES) $(GENINCLUDES)

# Libs' path
IUPPATH = -L$(MAINPATH)/3rd_party_libs/iup/iup-3.10.1_Linux35_64_lib/lib
LIBSPATH = $(IUPPATH)

# Libs
LGL = -lglut -lGLU -lGL -lGLEW
LIUP = -liup -liupgl -liupimglib
LIBS = $(LGL) $(LIUP) -lassimp

# Make directories
MKDIR = mkdir -p
DIR_BIN = $(MAINPATH)/bin
DIR_OBJ = obj
DIR_RELEASE = release
DIR_DEBUG = debug
DIR_PRODUCTION = production

all:
	$(CC) $(CFLAGS) $(DEFINES) -o engine $(MAINPATH)/src/application/main.cpp $(MAINPATH)/src/application/gui/MainWindowPresenter.cpp $(MAINPATH)/src/application/gui/MainWindow.cpp $(MAINPATH)/src/application/gui/PlyModel.cpp $(MAINPATH)/src/application/gui/ObjModel.cpp $(MAINPATH)/src/application/gui/OFFModel.cpp $(MAINPATH)/src/engine/GLModel.cpp $(MAINPATH)/src/engine/GLShader.cpp $(INCLUDES) $(LIBSPATH) $(LIBS)

directories:
	
tests:
	$(CC) -std=c++11 -isystem $(GTEST_PATH)/include $(GENINCLUDES) -pthread $(TESTS_PATH)/main.cpp $(GTEST_PATH)/lib/libgtest.a -o nutTests

clean:
	rm -rf *.o *~