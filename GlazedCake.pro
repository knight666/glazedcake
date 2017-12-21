TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += \
        source \
        examples

app.depends = source