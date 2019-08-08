
#include "dmgen.h"

#include "dmutil.h"
#include "dmparser.h"

#include "dmargparser.h"

#include "dmstrtk.hpp"

#include "dmcmake_package_bin.h"
#include "dmerror_package_bin.h"

#include <ctemplate/per_expand_data.h>
#include <ctemplate/template.h>
#include <ctemplate/template_dictionary.h>
#include <ctemplate/template_dictionary_interface.h>
#include <ctemplate/template_emitter.h>
#include <ctemplate/template_enums.h>
#include <ctemplate/template_modifiers.h>
#include <ctemplate/template_namelist.h>
#include <ctemplate/template_pathops.h>
#include <ctemplate/template_string.h>

#include <google/protobuf/compiler/command_line_interface.h>
#include <google/protobuf/compiler/cpp/cpp_generator.h>

#include "dmcpp_generator.h"

#include <fstream>

#define DMLog printf

CDMGen::CDMGen() {

}

CDMGen::~CDMGen() {

}

bool CDMGen::Init() {
    return true
           && true;
}

bool CDMGen::DoCommand( int argc, char** argv) {

    m_argc = argc;
    m_argv = argv;
    std::vector<std::string> vecCommand;

    for ( int i = 0; i < argc; i++ ) {
        std::string strCommand = argv[i];
        vecCommand.push_back( strCommand );
        //DMLog("%s\r\n", strCommand.c_str());
    }
    google::protobuf::compiler::CommandLineInterface cli;
    cli.AllowPlugins("protoc-");

    // Proto2 C++
    google::protobuf::compiler::cpp::DMCppGenerator cpp_generator;
    //cpp_generator.SetTPL(oDict);
    cli.RegisterGenerator("--cpp_out", "--cpp_opt", &cpp_generator,
        "Generate C++ header and source.");
    switch (cli.ParseArguments(m_argc, m_argv)) {
    case google::protobuf::compiler::CommandLineInterface::PARSE_ARGUMENT_DONE_AND_EXIT:
        DMLog("ParseArguments failed");
        return false;
    case google::protobuf::compiler::CommandLineInterface::PARSE_ARGUMENT_FAIL:
        DMLog("ParseArguments failed");
        return false;
    case google::protobuf::compiler::CommandLineInterface::PARSE_ARGUMENT_DONE_AND_CONTINUE:
        break;
    }

    if (cli.input_files_.empty()
        || cli.input_files_.size() > 1)
    {
        DMLog("ParseArguments failed");
        return false;
    }

    m_strUserPath = DMGetWorkPath();
    //DMLog("tool path: %s\r\n", m_strUserPath.c_str());

    for (int j=0; j < cli.input_files_.size(); j++)
    {
        std::string strProtoFile = cli.input_files_[j];

        m_strProtoName = strProtoFile.substr(0, strProtoFile.rfind('.') ==
            std::string::npos ? strProtoFile.length() :
            strProtoFile.rfind('.'));

        for (int i = ETPLTYPE_DMCMAKE__BEGIN; i < ETPLTYPE_DMCMAKE__END; ++i) {
            std::ofstream ofsh;

            std::string strFile = DMTPL_DMCMAKE_GetFileName(i);

            std::string strExpandFile = ExpandFileName(strFile);

            std::string strFullFilePath = m_strUserPath + PATH_DELIMITER + strExpandFile;

            std::string strPath = strFullFilePath.substr(0,
                strFullFilePath.rfind(PATH_DELIMITER));

            DMCreateDirectories(strPath.c_str());

            ofsh.open(strFullFilePath,
                std::ios::out | std::ios::binary);

            if (ofsh.fail()) {
                DMASSERT(0);
                continue;
            }

            ofsh << MakeFile(i);
        }
    }

    return true;
}

std::string CDMGen::MakeFile( int nType ) {
    tpl::TemplateDictionary oDict(ExpandFileName(DMTPL_DMCMAKE_GetFileName( nType )));
    std::string strOut;

    tpl::Template* poTemplate = tpl::Template::StringToTemplate(
                                    DMTPL_DMCMAKE_GetData(
                                        nType ), DMTPL_DMCMAKE_GetDataSize( nType ), ctemplate::DO_NOT_STRIP );

    if ( NULL == poTemplate ) {
        DMASSERT(0 && "Expand MakeFile failed.");
        return strOut;
    }

    OnSetData( oDict );
    OnSetPB( oDict );

    poTemplate->Expand( &strOut, &oDict );

    return strOut;
}

std::string CDMGen::ExpandFileName( const std::string& strFile ) {
    tpl::TemplateDictionary oDict("filename.tpl");

    std::string strOut;

    tpl::Template* poTemplate = tpl::Template::StringToTemplate( strFile.c_str(),
                                strFile.size(), ctemplate::DO_NOT_STRIP );

    if ( NULL == poTemplate ) {
			DMASSERT(0 && "ExpandFileName failed.");
        return strFile;
    }

    OnSetFileName( oDict );

    poTemplate->Expand( &strOut, &oDict );
    strtk::replace('|', PATH_DELIMITER, strOut);
    return strOut;
}

void CDMGen::OnSetData( tpl::TemplateDictionary& oDict ) {

    oDict.SetGlobalValue("GITHUB_USERNAME", "brinkqiang");
    oDict.SetGlobalValue("GITHUB_MAIL", "brink.qiang@gmail.com");
    oDict.SetGlobalValue("DMPROTO_NAME", m_strProtoName);
    oDict.SetGlobalValue("DMPROTO_NAME_UP", strtk::as_uppercase(m_strProtoName));
}


void CDMGen::OnSetPB(tpl::TemplateDictionary& oDict) {
    google::protobuf::compiler::CommandLineInterface cli;
    cli.AllowPlugins("protoc-");

    // Proto2 C++
    google::protobuf::compiler::cpp::DMCppGenerator cpp_generator;
    cpp_generator.SetTPL(oDict);
    cli.RegisterGenerator("--cpp_out", "--cpp_opt", &cpp_generator,
                          "Generate C++ header and source.");

    cli.Run(m_argc, m_argv);
}

void CDMGen::OnSetFileName( tpl::TemplateDictionary& oDict ) {
    oDict.SetGlobalValue("GITHUB_USERNAME", "brinkqiang");
    oDict.SetGlobalValue("GITHUB_MAIL", "brink.qiang@gmail.com");
    oDict.SetGlobalValue("DMPROTO_NAME", m_strProtoName);
    oDict.SetGlobalValue("DMPROTO_NAME_UP", strtk::as_uppercase(m_strProtoName));
}
