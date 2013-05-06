SOURCES += src/*.cpp
SOURCES -= src/support_win32.cpp

HEADERS += include/nori/*.h

RESOURCES += data/resources.qrc

INCLUDEPATH += include
DEPENDPATH += include data
OBJECTS_DIR = build
RCC_DIR = build
MOC_DIR = build
UI_DIR = build
DESTDIR = .

QT += xml xmlpatterns opengl

macx {
	OBJECTIVE_SOURCES += src/support_osx.m
	QMAKE_LFLAGS += -framework Cocoa -lobjc
	# The following is (strangely) needed for correct exception handling on Mac OS 10.6+
	QMAKE_CXXFLAGS_X86_64 -= -mmacosx-version-min=10.5
	QMAKE_CXXFLAGS_X86_64 += -mmacosx-version-min=10.6
}

macx | unix {
	QMAKE_CXXFLAGS_RELEASE -= -O2 
	QMAKE_CXXFLAGS += -O3 -march=nocona -msse2 -mfpmath=sse -fstrict-aliasing
	QMAKE_LIBDIR += /usr/local/lib
	INCLUDEPATH += /usr/include/OpenEXR /usr/local/include/OpenEXR
	LIBS += -lIlmImf -lIex
}

win32 {
	# You will have to update the following two lines based on where you have installed OpenEXR
	QMAKE_LIBDIR += ../openexr/Deploy/lib
	INCLUDEPATH += ../openexr/Deploy/include/OpenEXR ../boost_1_53_0

	QMAKE_CXXFLAGS += /O2 /fp:fast /GS- /GL /D_SCL_SECURE_NO_WARNINGS /D_CRT_SECURE_NO_WARNINGS
	QMAKE_LDFLAGS += /LTCG
	SOURCES += src/support_win32.cpp
	LIBS += IlmImf.lib Iex.lib IlmThread.lib Imath.lib Half.lib
}

TARGET = nori
CONFIG += console 
CONFIG -= app_bundle
