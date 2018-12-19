
#ifndef __DMGEN_H_INCLUDE__
#define __DMGEN_H_INCLUDE__


#include "dmsingleton.h"

#include "dmos.h"

#include <ctemplate/template_dictionary.h>

namespace tpl = ctemplate;

typedef struct tagFileInfo {
    std::string strFullPathFile;
    std::string strFullPath;
    std::string strModuleName;
    std::string strIDName;
    ///
    std::string strHFileName;
    std::string strHDataName;
} SPackFileInfo;

typedef std::vector<SPackFileInfo> VecFileInfo;
typedef VecFileInfo::iterator VecFileInfoIt;

class CDM_ERROR {
  public:
  public:
    CDM_ERROR() {
        m_strName = "";
        m_nID = 0;
        m_strInfo = "";
        m_strDes = "";
    }

  public:
    std::string& GetName() {
        return m_strName;    /// Name
    }

    int&                                 GetID() {
        return m_nID;    /// ID
    }

    std::string&                              GetInfo() {
        return m_strInfo;    /// Info
    }

    std::string&                              GetDes() {
        return m_strDes;    /// Des
    }

  public:

  private:
    std::string                              m_strName;
    int                                 m_nID;
    std::string                              m_strInfo;
    std::string                              m_strDes;
};

typedef std::vector<CDM_ERROR> CVecErrorCode;

class CDMGen : public CDMSafeSingleton<CDMGen> {
    friend class CDMSafeSingleton<CDMGen>;


  public:
    CDMGen();
    virtual ~CDMGen();

    bool Init();
    bool LoadError();
  public:
    // interface
    bool DoCommand( int argc, char* argv[] );
  public:
    // inner
    std::string MakeFile( int nType );
    std::string ExpandFileName( const std::string& strFile );

  public:
    // event
    void OnSetData( tpl::TemplateDictionary& oDict );
    void OnSetPB(tpl::TemplateDictionary& oDict);
    void OnSetFileName( tpl::TemplateDictionary& oDict );
  private:

    std::string m_strUserPath;
    std::string m_strProtoName;

    int m_argc;
    char** m_argv;
};

#endif // __DMGEN_H_INCLUDE__