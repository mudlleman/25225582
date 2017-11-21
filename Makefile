#############################################################################
# Makefile for building: agv
# Generated by qmake (2.01a) (Qt 4.7.3) on: ?? 4? 22 16:36:18 2017
# Project:  agv.pro
# Template: app
# Command: /opt/qt-4.7.3/bin/qmake -o Makefile agv.pro
#############################################################################

####### Compiler, tools and options

CC            = arm-none-linux-gnueabi-gcc
CXX           = arm-none-linux-gnueabi-g++
DEFINES       = -DQT_NO_DEBUG -DQT_XML_LIB -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/opt/qt-4.7.3/mkspecs/qws/linux-arm-gnueabi-g++ -I. -I/opt/qt-4.7.3/include/QtCore -I/opt/qt-4.7.3/include/QtNetwork -I/opt/qt-4.7.3/include/QtGui -I/opt/qt-4.7.3/include/QtXml -I/opt/qt-4.7.3/include -I. -I.
LINK          = arm-none-linux-gnueabi-g++
LFLAGS        = -Wl,-O1 -Wl,-rpath,/opt/qt-4.7.3/lib
LIBS          = $(SUBLIBS)  -L/opt/qt-4.7.3/lib -lQtXml -L/opt/qt-4.7.3/lib -lQtGui -lQtNetwork -lQtCore -lpthread 
AR            = arm-none-linux-gnueabi-ar cqs
RANLIB        = 
QMAKE         = /opt/qt-4.7.3/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = arm-none-linux-gnueabi-strip
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

SOURCES       = main.cpp \
		mainwindow.cpp \
		xsserial.cpp \
		getnavigation.cpp \
		controlcenter.cpp \
		pidcalculate.cpp \
		ccontrolbyte.cpp \
		owntimer.cpp \
		pathrfid.cpp \
		condition.cpp \
		work.cpp \
		gpio.cpp \
		control.cpp \
		madacontrol.cpp \
		readpath.cpp moc_mainwindow.cpp \
		moc_xsserial.cpp \
		moc_getnavigation.cpp \
		moc_controlcenter.cpp \
		moc_pidcalculate.cpp \
		moc_ccontrolbyte.cpp \
		moc_owntimer.cpp \
		moc_pathrfid.cpp \
		moc_condition.cpp \
		moc_work.cpp \
		moc_gpio.cpp \
		moc_control.cpp \
		moc_madacontrol.cpp \
		moc_readpath.cpp
OBJECTS       = main.o \
		mainwindow.o \
		xsserial.o \
		getnavigation.o \
		controlcenter.o \
		pidcalculate.o \
		ccontrolbyte.o \
		owntimer.o \
		pathrfid.o \
		condition.o \
		work.o \
		gpio.o \
		control.o \
		madacontrol.o \
		readpath.o \
		moc_mainwindow.o \
		moc_xsserial.o \
		moc_getnavigation.o \
		moc_controlcenter.o \
		moc_pidcalculate.o \
		moc_ccontrolbyte.o \
		moc_owntimer.o \
		moc_pathrfid.o \
		moc_condition.o \
		moc_work.o \
		moc_gpio.o \
		moc_control.o \
		moc_madacontrol.o \
		moc_readpath.o
DIST          = /opt/qt-4.7.3/mkspecs/common/g++.conf \
		/opt/qt-4.7.3/mkspecs/common/unix.conf \
		/opt/qt-4.7.3/mkspecs/common/linux.conf \
		/opt/qt-4.7.3/mkspecs/common/qws.conf \
		/opt/qt-4.7.3/mkspecs/qconfig.pri \
		/opt/qt-4.7.3/mkspecs/modules/qt_webkit_version.pri \
		/opt/qt-4.7.3/mkspecs/features/qt_functions.prf \
		/opt/qt-4.7.3/mkspecs/features/qt_config.prf \
		/opt/qt-4.7.3/mkspecs/features/exclusive_builds.prf \
		/opt/qt-4.7.3/mkspecs/features/default_pre.prf \
		/opt/qt-4.7.3/mkspecs/features/release.prf \
		/opt/qt-4.7.3/mkspecs/features/default_post.prf \
		/opt/qt-4.7.3/mkspecs/features/warn_on.prf \
		/opt/qt-4.7.3/mkspecs/features/qt.prf \
		/opt/qt-4.7.3/mkspecs/features/unix/thread.prf \
		/opt/qt-4.7.3/mkspecs/features/moc.prf \
		/opt/qt-4.7.3/mkspecs/features/resources.prf \
		/opt/qt-4.7.3/mkspecs/features/uic.prf \
		/opt/qt-4.7.3/mkspecs/features/yacc.prf \
		/opt/qt-4.7.3/mkspecs/features/lex.prf \
		/opt/qt-4.7.3/mkspecs/features/include_source_dir.prf \
		agv.pro
QMAKE_TARGET  = agv
DESTDIR       = 
TARGET        = agv

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

$(TARGET): ui_mainwindow.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: agv.pro  /opt/qt-4.7.3/mkspecs/qws/linux-arm-gnueabi-g++/qmake.conf /opt/qt-4.7.3/mkspecs/common/g++.conf \
		/opt/qt-4.7.3/mkspecs/common/unix.conf \
		/opt/qt-4.7.3/mkspecs/common/linux.conf \
		/opt/qt-4.7.3/mkspecs/common/qws.conf \
		/opt/qt-4.7.3/mkspecs/qconfig.pri \
		/opt/qt-4.7.3/mkspecs/modules/qt_webkit_version.pri \
		/opt/qt-4.7.3/mkspecs/features/qt_functions.prf \
		/opt/qt-4.7.3/mkspecs/features/qt_config.prf \
		/opt/qt-4.7.3/mkspecs/features/exclusive_builds.prf \
		/opt/qt-4.7.3/mkspecs/features/default_pre.prf \
		/opt/qt-4.7.3/mkspecs/features/release.prf \
		/opt/qt-4.7.3/mkspecs/features/default_post.prf \
		/opt/qt-4.7.3/mkspecs/features/warn_on.prf \
		/opt/qt-4.7.3/mkspecs/features/qt.prf \
		/opt/qt-4.7.3/mkspecs/features/unix/thread.prf \
		/opt/qt-4.7.3/mkspecs/features/moc.prf \
		/opt/qt-4.7.3/mkspecs/features/resources.prf \
		/opt/qt-4.7.3/mkspecs/features/uic.prf \
		/opt/qt-4.7.3/mkspecs/features/yacc.prf \
		/opt/qt-4.7.3/mkspecs/features/lex.prf \
		/opt/qt-4.7.3/mkspecs/features/include_source_dir.prf \
		/opt/qt-4.7.3/lib/libQtXml.prl \
		/opt/qt-4.7.3/lib/libQtCore.prl \
		/opt/qt-4.7.3/lib/libQtGui.prl \
		/opt/qt-4.7.3/lib/libQtNetwork.prl
	$(QMAKE) -o Makefile agv.pro
/opt/qt-4.7.3/mkspecs/common/g++.conf:
/opt/qt-4.7.3/mkspecs/common/unix.conf:
/opt/qt-4.7.3/mkspecs/common/linux.conf:
/opt/qt-4.7.3/mkspecs/common/qws.conf:
/opt/qt-4.7.3/mkspecs/qconfig.pri:
/opt/qt-4.7.3/mkspecs/modules/qt_webkit_version.pri:
/opt/qt-4.7.3/mkspecs/features/qt_functions.prf:
/opt/qt-4.7.3/mkspecs/features/qt_config.prf:
/opt/qt-4.7.3/mkspecs/features/exclusive_builds.prf:
/opt/qt-4.7.3/mkspecs/features/default_pre.prf:
/opt/qt-4.7.3/mkspecs/features/release.prf:
/opt/qt-4.7.3/mkspecs/features/default_post.prf:
/opt/qt-4.7.3/mkspecs/features/warn_on.prf:
/opt/qt-4.7.3/mkspecs/features/qt.prf:
/opt/qt-4.7.3/mkspecs/features/unix/thread.prf:
/opt/qt-4.7.3/mkspecs/features/moc.prf:
/opt/qt-4.7.3/mkspecs/features/resources.prf:
/opt/qt-4.7.3/mkspecs/features/uic.prf:
/opt/qt-4.7.3/mkspecs/features/yacc.prf:
/opt/qt-4.7.3/mkspecs/features/lex.prf:
/opt/qt-4.7.3/mkspecs/features/include_source_dir.prf:
/opt/qt-4.7.3/lib/libQtXml.prl:
/opt/qt-4.7.3/lib/libQtCore.prl:
/opt/qt-4.7.3/lib/libQtGui.prl:
/opt/qt-4.7.3/lib/libQtNetwork.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile agv.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/agv1.0.0 || $(MKDIR) .tmp/agv1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/agv1.0.0/ && $(COPY_FILE) --parents mainwindow.h xsserial.h getnavigation.h controlcenter.h pidcalculate.h ccontrolbyte.h owntimer.h pathrfid.h condition.h work.h gpio.h control.h madacontrol.h readpath.h .tmp/agv1.0.0/ && $(COPY_FILE) --parents main.cpp mainwindow.cpp xsserial.cpp getnavigation.cpp controlcenter.cpp pidcalculate.cpp ccontrolbyte.cpp owntimer.cpp pathrfid.cpp condition.cpp work.cpp gpio.cpp control.cpp madacontrol.cpp readpath.cpp .tmp/agv1.0.0/ && $(COPY_FILE) --parents mainwindow.ui .tmp/agv1.0.0/ && (cd `dirname .tmp/agv1.0.0` && $(TAR) agv1.0.0.tar agv1.0.0 && $(COMPRESS) agv1.0.0.tar) && $(MOVE) `dirname .tmp/agv1.0.0`/agv1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/agv1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_mainwindow.cpp moc_xsserial.cpp moc_getnavigation.cpp moc_controlcenter.cpp moc_pidcalculate.cpp moc_ccontrolbyte.cpp moc_owntimer.cpp moc_pathrfid.cpp moc_condition.cpp moc_work.cpp moc_gpio.cpp moc_control.cpp moc_madacontrol.cpp moc_readpath.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_mainwindow.cpp moc_xsserial.cpp moc_getnavigation.cpp moc_controlcenter.cpp moc_pidcalculate.cpp moc_ccontrolbyte.cpp moc_owntimer.cpp moc_pathrfid.cpp moc_condition.cpp moc_work.cpp moc_gpio.cpp moc_control.cpp moc_madacontrol.cpp moc_readpath.cpp
moc_mainwindow.cpp: mainwindow.h
	/opt/qt-4.7.3/bin/moc $(DEFINES) $(INCPATH) mainwindow.h -o moc_mainwindow.cpp

moc_xsserial.cpp: xsserial.h
	/opt/qt-4.7.3/bin/moc $(DEFINES) $(INCPATH) xsserial.h -o moc_xsserial.cpp

moc_getnavigation.cpp: owntimer.h \
		xsserial.h \
		getnavigation.h
	/opt/qt-4.7.3/bin/moc $(DEFINES) $(INCPATH) getnavigation.h -o moc_getnavigation.cpp

moc_controlcenter.cpp: getnavigation.h \
		owntimer.h \
		xsserial.h \
		pidcalculate.h \
		ccontrolbyte.h \
		condition.h \
		gpio.h \
		madacontrol.h \
		pathrfid.h \
		work.h \
		control.h \
		readpath.h \
		controlcenter.h
	/opt/qt-4.7.3/bin/moc $(DEFINES) $(INCPATH) controlcenter.h -o moc_controlcenter.cpp

moc_pidcalculate.cpp: pidcalculate.h
	/opt/qt-4.7.3/bin/moc $(DEFINES) $(INCPATH) pidcalculate.h -o moc_pidcalculate.cpp

moc_ccontrolbyte.cpp: ccontrolbyte.h
	/opt/qt-4.7.3/bin/moc $(DEFINES) $(INCPATH) ccontrolbyte.h -o moc_ccontrolbyte.cpp

moc_owntimer.cpp: owntimer.h
	/opt/qt-4.7.3/bin/moc $(DEFINES) $(INCPATH) owntimer.h -o moc_owntimer.cpp

moc_pathrfid.cpp: xsserial.h \
		owntimer.h \
		pathrfid.h
	/opt/qt-4.7.3/bin/moc $(DEFINES) $(INCPATH) pathrfid.h -o moc_pathrfid.cpp

moc_condition.cpp: gpio.h \
		madacontrol.h \
		xsserial.h \
		owntimer.h \
		condition.h
	/opt/qt-4.7.3/bin/moc $(DEFINES) $(INCPATH) condition.h -o moc_condition.cpp

moc_work.cpp: condition.h \
		gpio.h \
		madacontrol.h \
		xsserial.h \
		owntimer.h \
		control.h \
		work.h
	/opt/qt-4.7.3/bin/moc $(DEFINES) $(INCPATH) work.h -o moc_work.cpp

moc_gpio.cpp: gpio.h
	/opt/qt-4.7.3/bin/moc $(DEFINES) $(INCPATH) gpio.h -o moc_gpio.cpp

moc_control.cpp: gpio.h \
		madacontrol.h \
		xsserial.h \
		owntimer.h \
		control.h
	/opt/qt-4.7.3/bin/moc $(DEFINES) $(INCPATH) control.h -o moc_control.cpp

moc_madacontrol.cpp: xsserial.h \
		owntimer.h \
		madacontrol.h
	/opt/qt-4.7.3/bin/moc $(DEFINES) $(INCPATH) madacontrol.h -o moc_madacontrol.cpp

moc_readpath.cpp: readpath.h
	/opt/qt-4.7.3/bin/moc $(DEFINES) $(INCPATH) readpath.h -o moc_readpath.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_mainwindow.h
compiler_uic_clean:
	-$(DEL_FILE) ui_mainwindow.h
ui_mainwindow.h: mainwindow.ui
	/opt/qt-4.7.3/bin/uic mainwindow.ui -o ui_mainwindow.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

main.o: main.cpp mainwindow.h \
		controlcenter.h \
		getnavigation.h \
		owntimer.h \
		xsserial.h \
		pidcalculate.h \
		ccontrolbyte.h \
		condition.h \
		gpio.h \
		madacontrol.h \
		pathrfid.h \
		work.h \
		control.h \
		readpath.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

mainwindow.o: mainwindow.cpp mainwindow.h \
		ui_mainwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o mainwindow.cpp

xsserial.o: xsserial.cpp xsserial.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o xsserial.o xsserial.cpp

getnavigation.o: getnavigation.cpp getnavigation.h \
		owntimer.h \
		xsserial.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o getnavigation.o getnavigation.cpp

controlcenter.o: controlcenter.cpp controlcenter.h \
		getnavigation.h \
		owntimer.h \
		xsserial.h \
		pidcalculate.h \
		ccontrolbyte.h \
		condition.h \
		gpio.h \
		madacontrol.h \
		pathrfid.h \
		work.h \
		control.h \
		readpath.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o controlcenter.o controlcenter.cpp

pidcalculate.o: pidcalculate.cpp pidcalculate.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o pidcalculate.o pidcalculate.cpp

ccontrolbyte.o: ccontrolbyte.cpp ccontrolbyte.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ccontrolbyte.o ccontrolbyte.cpp

owntimer.o: owntimer.cpp owntimer.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o owntimer.o owntimer.cpp

pathrfid.o: pathrfid.cpp pathrfid.h \
		xsserial.h \
		owntimer.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o pathrfid.o pathrfid.cpp

condition.o: condition.cpp condition.h \
		gpio.h \
		madacontrol.h \
		xsserial.h \
		owntimer.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o condition.o condition.cpp

work.o: work.cpp work.h \
		condition.h \
		gpio.h \
		madacontrol.h \
		xsserial.h \
		owntimer.h \
		control.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o work.o work.cpp

gpio.o: gpio.cpp gpio.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o gpio.o gpio.cpp

control.o: control.cpp control.h \
		gpio.h \
		madacontrol.h \
		xsserial.h \
		owntimer.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o control.o control.cpp

madacontrol.o: madacontrol.cpp madacontrol.h \
		xsserial.h \
		owntimer.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o madacontrol.o madacontrol.cpp

readpath.o: readpath.cpp readpath.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o readpath.o readpath.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

moc_xsserial.o: moc_xsserial.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_xsserial.o moc_xsserial.cpp

moc_getnavigation.o: moc_getnavigation.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_getnavigation.o moc_getnavigation.cpp

moc_controlcenter.o: moc_controlcenter.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_controlcenter.o moc_controlcenter.cpp

moc_pidcalculate.o: moc_pidcalculate.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_pidcalculate.o moc_pidcalculate.cpp

moc_ccontrolbyte.o: moc_ccontrolbyte.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_ccontrolbyte.o moc_ccontrolbyte.cpp

moc_owntimer.o: moc_owntimer.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_owntimer.o moc_owntimer.cpp

moc_pathrfid.o: moc_pathrfid.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_pathrfid.o moc_pathrfid.cpp

moc_condition.o: moc_condition.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_condition.o moc_condition.cpp

moc_work.o: moc_work.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_work.o moc_work.cpp

moc_gpio.o: moc_gpio.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_gpio.o moc_gpio.cpp

moc_control.o: moc_control.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_control.o moc_control.cpp

moc_madacontrol.o: moc_madacontrol.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_madacontrol.o moc_madacontrol.cpp

moc_readpath.o: moc_readpath.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_readpath.o moc_readpath.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

