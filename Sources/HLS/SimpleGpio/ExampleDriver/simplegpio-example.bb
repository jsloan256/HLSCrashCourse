#
# This file is the simplegpio-example recipe.
#

SUMMARY = "Simple simplegpio-example application"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://simplegpio-example.cpp \
           file://xsimplegpiosyn.c \
           file://xsimplegpiosyn_linux.c \
           file://xsimplegpiosyn.h \
           file://xsimplegpiosyn_hw.h \
           file://Makefile \
		  "

S = "${WORKDIR}"

do_compile() {
	     oe_runmake
}

do_install() {
	     install -d ${D}${bindir}
	     install -m 0755 simplegpio-example ${D}${bindir}
}
