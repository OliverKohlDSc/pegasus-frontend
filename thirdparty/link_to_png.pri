!isEmpty(PNG_LIBS) {
    LIBS += $${PNG_LIBS}
}
!isEmpty(PNG_INCLUDES) {
    INCLUDEPATH += $${PNG_INCLUDES}
    DEPENDPATH += $${PNG_INCLUDES}
}
