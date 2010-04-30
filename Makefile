#############################################################################
# Makefile for building: qgcide
# Generated by qmake (2.01a) (Qt 4.6.1) on: Fri Apr 30 13:43:56 2010
# Project:  qgcide.pro
# Template: app
# Command: /home/radek/qtsdk-2010.01/qt/bin/qmake -spec ../../../../qtsdk-2010.01/qt/mkspecs/linux-g++-64 -unix CONFIG+=debug -o Makefile qgcide.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -m64 -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -m64 -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I../../../../qtsdk-2010.01/qt/mkspecs/linux-g++-64 -I. -I../../../../qtsdk-2010.01/qt/include/QtCore -I../../../../qtsdk-2010.01/qt/include/QtNetwork -I../../../../qtsdk-2010.01/qt/include/QtGui -I../../../../qtsdk-2010.01/qt/include -I.
LINK          = g++
LFLAGS        = -m64 -Wl,-rpath,/home/radek/qtsdk-2010.01/qt/lib
LIBS          = $(SUBLIBS)  -L/home/radek/qtsdk-2010.01/qt/lib -lQtGui -L/home/radek/qtsdk-2010.01/qt/lib -L/usr/X11R6/lib64 -lQtNetwork -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /home/radek/qtsdk-2010.01/qt/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = src/main.cpp \
		src/qgcide.cpp 
OBJECTS       = main.o \
		qgcide.o
DIST          = ../../../../qtsdk-2010.01/qt/mkspecs/common/g++.conf \
		../../../../qtsdk-2010.01/qt/mkspecs/common/unix.conf \
		../../../../qtsdk-2010.01/qt/mkspecs/common/linux.conf \
		../../../../qtsdk-2010.01/qt/mkspecs/qconfig.pri \
		../../../../qtsdk-2010.01/qt/mkspecs/features/qt_functions.prf \
		../../../../qtsdk-2010.01/qt/mkspecs/features/qt_config.prf \
		../../../../qtsdk-2010.01/qt/mkspecs/features/exclusive_builds.prf \
		../../../../qtsdk-2010.01/qt/mkspecs/features/default_pre.prf \
		../../../../qtsdk-2010.01/qt/mkspecs/features/debug.prf \
		../../../../qtsdk-2010.01/qt/mkspecs/features/default_post.prf \
		../../../../qtsdk-2010.01/qt/mkspecs/features/warn_on.prf \
		../../../../qtsdk-2010.01/qt/mkspecs/features/qt.prf \
		../../../../qtsdk-2010.01/qt/mkspecs/features/unix/thread.prf \
		../../../../qtsdk-2010.01/qt/mkspecs/features/moc.prf \
		../../../../qtsdk-2010.01/qt/mkspecs/features/resources.prf \
		../../../../qtsdk-2010.01/qt/mkspecs/features/uic.prf \
		../../../../qtsdk-2010.01/qt/mkspecs/features/yacc.prf \
		../../../../qtsdk-2010.01/qt/mkspecs/features/lex.prf \
		../../../../qtsdk-2010.01/qt/mkspecs/features/include_source_dir.prf \
		qgcide.pro
QMAKE_TARGET  = qgcide
DESTDIR       = 
TARGET        = qgcide

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: qgcide.pro  ../../../../qtsdk-2010.01/qt/mkspecs/linux-g++-64/qmake.conf ../../../../qtsdk-2010.01/qt/mkspecs/common/g++.conf \
		../../../../qtsdk-2010.01/qt/mkspecs/common/unix.conf \
		../../../../qtsdk-2010.01/qt/mkspecs/common/linux.conf \
		../../../../qtsdk-2010.01/qt/mkspecs/qconfig.pri \
		../../../../qtsdk-2010.01/qt/mkspecs/features/qt_functions.prf \
		../../../../qtsdk-2010.01/qt/mkspecs/features/qt_config.prf \
		../../../../qtsdk-2010.01/qt/mkspecs/features/exclusive_builds.prf \
		../../../../qtsdk-2010.01/qt/mkspecs/features/default_pre.prf \
		../../../../qtsdk-2010.01/qt/mkspecs/features/debug.prf \
		../../../../qtsdk-2010.01/qt/mkspecs/features/default_post.prf \
		../../../../qtsdk-2010.01/qt/mkspecs/features/warn_on.prf \
		../../../../qtsdk-2010.01/qt/mkspecs/features/qt.prf \
		../../../../qtsdk-2010.01/qt/mkspecs/features/unix/thread.prf \
		../../../../qtsdk-2010.01/qt/mkspecs/features/moc.prf \
		../../../../qtsdk-2010.01/qt/mkspecs/features/resources.prf \
		../../../../qtsdk-2010.01/qt/mkspecs/features/uic.prf \
		../../../../qtsdk-2010.01/qt/mkspecs/features/yacc.prf \
		../../../../qtsdk-2010.01/qt/mkspecs/features/lex.prf \
		../../../../qtsdk-2010.01/qt/mkspecs/features/include_source_dir.prf \
		/home/radek/qtsdk-2010.01/qt/lib/libQtGui.prl \
		/home/radek/qtsdk-2010.01/qt/lib/libQtCore.prl \
		/home/radek/qtsdk-2010.01/qt/lib/libQtNetwork.prl
	$(QMAKE) -spec ../../../../qtsdk-2010.01/qt/mkspecs/linux-g++-64 -unix CONFIG+=debug -o Makefile qgcide.pro
../../../../qtsdk-2010.01/qt/mkspecs/common/g++.conf:
../../../../qtsdk-2010.01/qt/mkspecs/common/unix.conf:
../../../../qtsdk-2010.01/qt/mkspecs/common/linux.conf:
../../../../qtsdk-2010.01/qt/mkspecs/qconfig.pri:
../../../../qtsdk-2010.01/qt/mkspecs/features/qt_functions.prf:
../../../../qtsdk-2010.01/qt/mkspecs/features/qt_config.prf:
../../../../qtsdk-2010.01/qt/mkspecs/features/exclusive_builds.prf:
../../../../qtsdk-2010.01/qt/mkspecs/features/default_pre.prf:
../../../../qtsdk-2010.01/qt/mkspecs/features/debug.prf:
../../../../qtsdk-2010.01/qt/mkspecs/features/default_post.prf:
../../../../qtsdk-2010.01/qt/mkspecs/features/warn_on.prf:
../../../../qtsdk-2010.01/qt/mkspecs/features/qt.prf:
../../../../qtsdk-2010.01/qt/mkspecs/features/unix/thread.prf:
../../../../qtsdk-2010.01/qt/mkspecs/features/moc.prf:
../../../../qtsdk-2010.01/qt/mkspecs/features/resources.prf:
../../../../qtsdk-2010.01/qt/mkspecs/features/uic.prf:
../../../../qtsdk-2010.01/qt/mkspecs/features/yacc.prf:
../../../../qtsdk-2010.01/qt/mkspecs/features/lex.prf:
../../../../qtsdk-2010.01/qt/mkspecs/features/include_source_dir.prf:
/home/radek/qtsdk-2010.01/qt/lib/libQtGui.prl:
/home/radek/qtsdk-2010.01/qt/lib/libQtCore.prl:
/home/radek/qtsdk-2010.01/qt/lib/libQtNetwork.prl:
qmake:  FORCE
	@$(QMAKE) -spec ../../../../qtsdk-2010.01/qt/mkspecs/linux-g++-64 -unix CONFIG+=debug -o Makefile qgcide.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/qgcide1.0.0 || $(MKDIR) .tmp/qgcide1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/qgcide1.0.0/ && $(COPY_FILE) --parents src/qgcide.h .tmp/qgcide1.0.0/ && $(COPY_FILE) --parents src/main.cpp src/qgcide.cpp .tmp/qgcide1.0.0/ && (cd `dirname .tmp/qgcide1.0.0` && $(TAR) qgcide1.0.0.tar qgcide1.0.0 && $(COMPRESS) qgcide1.0.0.tar) && $(MOVE) `dirname .tmp/qgcide1.0.0`/qgcide1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/qgcide1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all:
compiler_moc_header_clean:
compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: 

####### Compile

main.o: src/main.cpp src/qgcide.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o src/main.cpp

qgcide.o: src/qgcide.cpp src/qgcide.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qgcide.o src/qgcide.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:
