TEMPLATE=app
TARGET=qgcide

CONFIG+=qtopia
DEFINES+=QTOPIA

# I18n info
STRING_LANGUAGE=en_US
LANGUAGES=en_US

INCLUDEPATH+=/usr/include/glib-2.0 \
             /usr/lib/glib-2.0/include

LIBS+=-lglib-2.0

# Package info
pkg [
    name=qdictopia
    desc="A Dictionary Program for GCIDE"
    license=GPLv2
    version=1.0
    maintainer="Radek Polak <psonek2@seznam.cz>"
]

# Input files
HEADERS=\
    src/qgcide.h

SOURCES=\
    src/main.cpp \
    src/qgcide.cpp \

# Install rules
target [
    hint=sxe
    domain=untrusted
]

desktop [
    hint=desktop
    files=qgcide.desktop
    path=/apps/Applications
]

pics [
    hint=pics
    files=pics/*
    path=/pics/qgcide
]

help [
    hint=help
    source=help
    files=*.html
]