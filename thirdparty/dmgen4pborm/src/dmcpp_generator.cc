
#include "dmcpp_generator.h"

#include <vector>
#include <memory>
#ifndef _SHARED_PTR_H
#include <google/protobuf/stubs/shared_ptr.h>
#endif
#include <utility>

#include <google/protobuf/compiler/cpp/cpp_file.h>
#include <google/protobuf/compiler/cpp/cpp_helpers.h>
#include <google/protobuf/io/printer.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/stubs/strutil.h>
#include <google/protobuf/compiler/cpp/cpp_field.h>
#include <ctemplate/template_dictionary.h>
#include "dmstrtk.hpp"

namespace google {
namespace protobuf {
namespace compiler {
namespace cpp {

DMCppGenerator::DMCppGenerator() {}
DMCppGenerator::~DMCppGenerator() {}

void DMCppGenerator::SetTPL(ctemplate::TemplateDictionary& oDict) {
    m_poDict = &oDict;
}

bool DMCppGenerator::Generate(const FileDescriptor* file,
                              const string& parameter,
                              GeneratorContext* generator_context,
                              string* error) const {
    std::vector<std::pair<string, string> > options;
    ParseGeneratorParameter(parameter, &options);

    Options file_options;
    bool split_source = false;

    for (int i = 0; i < (int)options.size(); i++) {
        if (options[i].first == "dllexport_decl") {
            file_options.dllexport_decl = options[i].second;
        }
        else if (options[i].first == "safe_boundary_check") {
            file_options.safe_boundary_check = true;
        }
        else if (options[i].first == "annotate_headers") {
            file_options.annotate_headers = true;
        }
        else if (options[i].first == "annotation_pragma_name") {
            file_options.annotation_pragma_name = options[i].second;
        }
        else if (options[i].first == "annotation_guard_name") {
            file_options.annotation_guard_name = options[i].second;
        }
        else if (options[i].first == "lite") {
            file_options.enforce_lite = true;
        }
        else if (options[i].first == "lite_implicit_weak_fields") {
            file_options.lite_implicit_weak_fields = true;
        }
        else if (options[i].first == "table_driven_parsing") {
            file_options.table_driven_parsing = true;
        }
        else if (options[i].first == "table_driven_serialization") {
            file_options.table_driven_serialization = true;
        }
        else if (options[i].first == "split_source") {
            split_source = true;
        }
        else {
            *error = "Unknown generator option: " + options[i].first;
            return false;
        }
    }

    // -----------------------------------------------------------------


    string basename = StripProto(file->name());

    FileGenerator file_generator(file, file_options);

    m_poDict->SetGlobalValue("DMPROTO_NAME", basename);
    m_poDict->SetGlobalValue("DMPROTO_FILE_NAME", basename + ".orm.h");
    m_poDict->SetGlobalValue("DMPACKAGE_NAME", file->package());

    ctemplate::TemplateDictionary* poPackageList =
        m_poDict->AddSectionDictionary("DMPACKAGE_LIST");
    if (NULL == poPackageList)
    {
        return false;
    }

    for (int i = 0; i < (int)file_generator.message_generators_.size(); i++) {
        MessageGenerator* poMessage = file_generator.message_generators_[i];

        if (NULL == poMessage) {
            *error = "Unknown Message";
            return false;
        }

        GenMessageList(poMessage);
    }

    return true;
}

void DMCppGenerator::GenMessageList(MessageGenerator* poMessage) const
{
	ctemplate::TemplateDictionary* poMessageEnum =
		m_poDict->AddSectionDictionary("DMMESSAGE_LIST");

	if (poMessageEnum) {
		std::string strMessageName = poMessage->classname_;

        poMessageEnum->SetValue("DMMESSAGE_NAME", strMessageName);
        poMessageEnum->SetValue("DMMESSAGE_NAME_UP", strtk::as_uppercase(strMessageName));
        poMessageEnum->SetValue("DMMESSAGE_CPP_NAME", QualifiedClassName(poMessage->descriptor_));
        
		std::cout << poMessage->descriptor_->DebugString() << std::endl;

        for (int i = 0; i < (int)poMessage->descriptor_->field_count(); i++)
        {
            const FieldDescriptor* field = poMessage->descriptor_->field(i);
            if (NULL == field)
            {
                assert(0);
                return;
            }
            if (field->is_repeated()
                || field->is_map()) {
                continue;
            }

            if (0 == i)
            {
                poMessageEnum->SetValue("DMMESSAGE_FIRST_FIELD_NAME", FieldName(field));
            }


            ctemplate::TemplateDictionary* poFieldEnum =
                poMessageEnum->AddSectionDictionary("DMFIELD_LIST");
            if (poFieldEnum) {

                if (i == poMessage->descriptor_->field_count() - 1)
                {
                    poFieldEnum->SetValue("DMFIELD_COMMA", "DM_MAGIC_END");
                }
                else
                {
                    poFieldEnum->SetValue("DMFIELD_COMMA", "DM_MAGIC");
                }

                switch (field->cpp_type())
                {
                case FieldDescriptor::CPPTYPE_STRING:
                {
                    poFieldEnum->SetValue("DMFIELD_TYPE", "string");
                    poFieldEnum->SetValue("DMFIELD_SQL_TYPE", "MEDIUMTEXT");
                    break;
                }
                case FieldDescriptor::CPPTYPE_ENUM:
                case FieldDescriptor::CPPTYPE_INT32:
                case FieldDescriptor::CPPTYPE_INT64:
                case FieldDescriptor::CPPTYPE_UINT32:
                case FieldDescriptor::CPPTYPE_UINT64:
                {
                    poFieldEnum->SetValue("DMFIELD_TYPE", "int");
                    poFieldEnum->SetValue("DMFIELD_SQL_TYPE", "BIGINT");
                    break;
                }
                case FieldDescriptor::CPPTYPE_FLOAT:
                case FieldDescriptor::CPPTYPE_DOUBLE:
                {
                    poFieldEnum->SetValue("DMFIELD_TYPE", "int");
                    poFieldEnum->SetValue("DMFIELD_SQL_TYPE", "BIGINT");
                    break;
                }
                default:
                    break;
                }

                std::string strDeclaredTypeMethodName = DeclaredTypeMethodName(field->type());
                poFieldEnum->SetValue("DMFIELD_NAME", FieldName(field));
                poFieldEnum->SetValue("DMFIELD_NAME_UP", strtk::as_uppercase(FieldName(field)));

                if (field->cpp_type() == FieldDescriptor::CPPTYPE_MESSAGE) {
                    poFieldEnum->SetValue("DMFIELD_CPP_NAME", FieldMessageTypeName(field));
                }
                else if (field->cpp_type() == FieldDescriptor::CPPTYPE_ENUM)
                {
                    poFieldEnum->SetValue("DMFIELD_CPP_NAME", QualifiedClassName(field->enum_type()));
                }
                else {
                    poFieldEnum->SetValue("DMFIELD_CPP_NAME", PrimitiveTypeName(field->cpp_type()));
                }
            }
        }
    }
}

}  // namespace cpp
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
