import qbs 1.0

Project {

    name: "kldap.sln"

    DynamicLibrary {
        name: "kldap"

        Depends { name: "cpp" }

        files: [
            "src/ber.cpp",
            "src/ber.h",
            "src/ldapattributeproxymodel.cpp",
            "src/ldapattributeproxymodel.h",
            "src/ldapconfigwidget.cpp",
            "src/ldapconfigwidget.h",
            "src/ldapconnection.cpp",
            "src/ldapconnection.h",
            "src/ldapcontrol.cpp",
            "src/ldapcontrol.h",
            "src/ldapdefs.h",
            "src/ldapdn.cpp",
            "src/ldapdn.h",
            "src/ldapmodel.cpp",
            "src/ldapmodel.h",
            "src/ldapmodelnode_p.cpp",
            "src/ldapmodelnode_p.h",
            "src/ldapmodel_p.cpp",
            "src/ldapmodel_p.h",
            "src/ldapobject.cpp",
            "src/ldapobject.h",
            "src/ldapoperation.cpp",
            "src/ldapoperation.h",
            "src/ldapsearch.cpp",
            "src/ldapsearch.h",
            "src/ldapserver.cpp",
            "src/ldapserver.h",
            "src/ldapstructureproxymodel.cpp",
            "src/ldapstructureproxymodel.h",
            "src/ldapurl.cpp",
            "src/ldapurl.h",
            "src/ldif.cpp",
            "src/ldif.h",
        ]

        Group {
            name: "Win32 files"

            files: [
                "src/w32-ldap-help.h",
            ]
        }

        Group {
            name: "KDE files"

            files: [
            ]
        }

        Group {
            name: "CMake files"

            files: [
                "src/CMakeLists.txt",
                "src/kldap_config.h.cmake",
            ]
        }

        Group {
            name: "Misc files"

            files: [
                "src/Messages.sh",
            ]
        }
    }

}

