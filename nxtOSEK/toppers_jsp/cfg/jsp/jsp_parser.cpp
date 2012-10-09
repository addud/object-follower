/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 * 
 *  �嵭����Ԥϡ��ʲ��� (1)��(4) �ξ�狼��Free Software Foundation 
 *  �ˤ�äƸ�ɽ����Ƥ��� GNU General Public License �� Version 2 �˵�
 *  �Ҥ���Ƥ���������������˸¤ꡤ�ܥ��եȥ��������ܥ��եȥ�����
 *  ����Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ�������ѡ������ۡʰʲ���
 *  ���ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
 *      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
 *      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
 *      �ȡ�
 *    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����
 *  �ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ
 *  ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���
 * 
 *  @(#) $Id: jsp_parser.cpp,v 1.60 2004/09/09 19:22:41 takayuki Exp $
 */

// $Header: /home/CVS/configurator/jsp/jsp_parser.cpp,v 1.60 2004/09/09 19:22:41 takayuki Exp $

#include <stdarg.h>

#include "jsp/jsp_defs.h"
#include "base/parser.h"
#include "base/mpstrstream.h"
#include "jsp/jsp_common.h"

#include <set>
#include <map>
#include <cctype>
#include <algorithm>
#include <iomanip>

using namespace ToppersJsp;
using namespace std;

class CoreParser : public ParserComponent
{
protected:
    virtual void parseOption(Directory &);
            void outputContainer(Directory & container) throw();
            void assignID(Directory & container) throw();

public:
    CoreParser(void);
    virtual bool parse(Parser & p, Directory & container);
} instance_of_Parser;

CoreParser::CoreParser(void)
{
    setBanner("=== TOPPERS/JSP Kernel Configurator ver.9.4 (for JSP rel 1.4) ===");
}

void CoreParser::parseOption(Directory & container)
{
    ParserComponent::parseOption(container);

    if(findOption("h","help"))
    {
        cerr << Message(
            "  -obj, --dump-object=filename : Dump the object tree into the file specified\n"
            "  -ao, --assign-order=order : Specify the order of automatic ID assignment\n"
            "    You can use three terms below as ordering rule.\n"
            "     alphabetic (in alphabetic order)\n"
            "     fcfs       (in arrival order [as default])\n"
            "     reverse    (reverse the order)\n"
            "  -var, --variable-id : Prepare ID-variable for storing its identifier number\n",
            "  -obj, --dump-object=�ե�����̾ : ���ꤷ���ե�����˥��֥������Ⱦ������Ϥ��ޤ�\n"
            "  -ao, --assign-order=��� : ��ưID�����γ����������ꤷ�ޤ�\n"
            "    ��������ϼ���3�Ĥ��ȹ礻�ǻ��ꤷ�ޤ�.\n"
            "     alphabetic (ABC��), fcfs (����� [�ǥե����]), reverse (�ս�)\n"
            "  -var, --variable-id : ID�ֹ���Ǽ�����ѿ����Ѱդ��ޤ�");
        return;
    }

    checkOption("D","dump");
    checkOption("cpu","cpu");
    checkOption("system","system");
    checkOption("var","variable-id");
}

namespace {
	int displayHandler(Directory & container, const char * category, const char * format)
	{
	    Directory * node  = 0;
	    Directory * scope = 0;

	    node = container.findChild(OBJECTTREE,category,NULL);
	    if(node == 0 || node->size() == 0)
		return 0;

	    VerboseMessage("Handler assignment list [%]\n","�ϥ�ɥ����ɽ [%]\n") << category;

	    scope = node->getFirstChild();
	    while(scope != 0)
	    {
		VerboseMessage::getStream() << scope->format(format);
		scope = scope->getNext();
	    }

	    return node->size();
	}

	//�ޥ������줿toupper��ؿ������� (STL-algorithm��)
	int toupper_function(int c)
	{ return toupper(c); }
}
/*
 *  outputContainer - �ǥХå��� or ����׻�����˥��֥������Ⱦ�������Υե���������ǽ��Ϥ���
 */
void CoreParser::outputContainer(Directory & container) throw()
{
    try {

        if(findOption("D","dump") || findOption("debug","debug")) {
            fstream file("container.txt", ios::out);
            container.drawTree(&file);
            file.close();
        }

        if(findOption("Dx","dump-xml") || findOption("debug","debug")) {
            fstream file("container.xml", ios::out);
            container.drawTree_byXML(&file);
            file.close();
        }
    }
    catch (...) {
    }
}

/*
 *  assignID - ���֥������Ȥ��Ф���ID�����դ���
 *             ����������֥�������̾��桼�����󼨤���
 */
void CoreParser::assignID(Directory & container) throw()
{
    multimap<int, const char *> sorter;
    multimap<int, const char *>::iterator scope;
    enum Common::tagAssignmentOrder order = Common::FCFS;

    sorter.insert(pair<int, const char *>(container[OBJECTTREE "/" TASK].size(), TASK));
    sorter.insert(pair<int, const char *>(container[OBJECTTREE "/" SEMAPHORE].size(), SEMAPHORE));
    sorter.insert(pair<int, const char *>(container[OBJECTTREE "/" EVENTFLAG].size(), EVENTFLAG));
    sorter.insert(pair<int, const char *>(container[OBJECTTREE "/" DATAQUEUE].size(), DATAQUEUE));
    sorter.insert(pair<int, const char *>(container[OBJECTTREE "/" MAILBOX].size(), MAILBOX));
    sorter.insert(pair<int, const char *>(container[OBJECTTREE "/" FIXEDSIZEMEMORYPOOL].size(), FIXEDSIZEMEMORYPOOL));
    sorter.insert(pair<int, const char *>(container[OBJECTTREE "/" CYCLICHANDLER].size(), CYCLICHANDLER));

    order = Common::parseOrder(getOption("ao", "assign-order"));
    scope = sorter.begin();
    while(scope != sorter.end())
    {
        if( (*scope).first != 0 )
            Common::assignID(container, (*scope).second, OBJECTTREE, order);
        ++ scope;
    }

    displayHandler(container, INTERRUPTHANDLER, "  $@ : $(inthdr)\n");
    displayHandler(container, EXCEPTIONHANDLER, "  $@ : $(exchdr)\n");
    displayHandler(container, INITIALIZER, "  $@ : $(inirtn)($(exinf))\n");
    displayHandler(container, TERMINATOR, "  $@ : $(terrtn)($(exinf))\n");
}


bool CoreParser::parse(Parser & p, Directory & container)
{
    Token token;
    string work;
    bool isParseErrorOccured;

    if(findOption("cpu","cpu", &work))
        container["/cpu"] = work;
    
    try{
        isParseErrorOccured = false;
        do {
            p.getToken(token);
            if(token == Token::IDENTIFIER)
            {
                    /* ���顼�������Ƥ����³�������Τǡ�
                        ���������Ȥ����Ф��Ƥ����Ƥɤ�ɤ�³���� */
                try 
                {   this->parseStaticAPI(p, container, token);  }
                catch(...)
                {   isParseErrorOccured = true;                 }

            }
        }while(token != Token::EOS);

        p.setLogBuffer(NULL);

        if(isParseErrorOccured)
            ExceptionMessage(ExceptionMessage::FATAL,"The configuration process was aborted due to occurence of parse error","��ʸ���Ϥ˼��Ԥ���������������Ǥ��ޤ�").throwException();

        if(container[OBJECTTREE "/" TASK].size() == 0)
            ExceptionMessage("Kernel requires one or more task objects.","���������֥������Ȥ�����ޤ���").throwException();

            /* ID���� & ���֥�������̾ɽ�� */
        assignID(container);

            /* ���֥������Ⱦ����ե�����˽��� */
        outputContainer(container);

        return true;
    }
    catch(Exception &)
    {
            /* �㳰���ꤲ�ʤ������� ���ߤΥ��֥������Ⱦ�����Ǽ���� */
        outputContainer(container);
        throw;
    }
}

/* ======================================================================== */

DECLARE_DIRECTIVE(assigner,"assign_id")
{
    Token name;
    Token value;

    p.getToken(name, Token::IDENTIFIER);
    p.getToken(value, Token::INTEGER);

    if(value.value <= 0)
        ExceptionMessage("Cannot assign an ID number less or equal to 0.","0�ʲ���ID�ֹ�����ꤹ�뤳�ȤϤǤ��ޤ���").throwException();

    *container.openChild("/","identifier",name.c_str(),NULL) = value.value;
}

DECLARE_DIRECTIVE(parameter,"parameter")
{
    Token token;
    string key;
    string::size_type i,j;

    do {
        p.getToken(token);
        if(!(token == Token::STRINGLITERAL))
            ExceptionMessage("parameter pragma requires additional parameter put in '\"...\"'","parameter�ץ饰�ޤˤ�\"...\"�ǳ��줿�ɲåѥ�᡼����ɬ�פǤ�").throwException();

        token.chopLiteral();

        if(token[0] == '-')
        {
            i = token.find_first_of('=');
            j = token.find_first_not_of('-');
            if(i == j || j == string::npos)
                ExceptionMessage(ExceptionMessage::FATAL,"Wrong option [%]","�����ʥ��ץ���� [%]") << token << throwException;

            if(i != string::npos)
            {
                key = DEFAULT_PARAMETER;
                *container.openChild(string("/Parameter/") + token.substr(1, i-1)) = token.substr(i+1);
            }
            else
            {
                key = token.substr(1);
                *container.openChild(string("/Parameter/") + key) = string("");
            }
        }else
            *container.openChild(string("/Parameter/") + key) = token;

        p.getToken(token);
    } while(token.compare(",") == 0);

    p.putBack(token);
}


/* ======================================================================== */
class ConfigurationFileGenerator : public Component
{
protected:
    bool backward_compatible;
    bool libstyle_include;
    bool restrict_zero;
    bool def_prototype;

    enum tagDefinition { HEADER=1, TNUM=2, BUFFER=4, DEFINITION=8, CONTROLBLOCK=16, SHORT_ID=32, TNUMNO=64, INIT=128, PROTOTYPE=256, INITLIST=512 };
    void createObjectDefinition(MultipartStream *, Directory &, int, ...);

    virtual void parseOption(Directory &);
    virtual void body(Directory &);
    virtual void onFatalExit(Directory &);

public:
    ConfigurationFileGenerator(void) : Component(CODEGENERATOR) {};
} instance_of_Configurator;



namespace {

        //�ե�����̾�μ���
    string get_filename(string category, string _default) throw(Exception)
    {
        string result(_default);
        OptionParameter::OptionItem item = getOptionParameter()[category];

        if(item.isValid()) {
            if(item.countParameter() == 1)
                result = item[0];
            else
                ExceptionMessage("-% should have just ONE filename.","-%���ץ����˻���Ǥ���ե������1�ĤΤ�") << category << throwException;
        }

        if(result.empty())
            ExceptionMessage("-% has illegal file name.","-%���ץ������Ϥ��줿�ե�����̾������") << category << throwException;
        
        return result;
    }

        // �����ͥ빽���ե����������
    KernelCfg * createKernelCfg(void)
    {
        KernelCfg * cfg;

        cfg = KernelCfg::createInstance(get_filename("kernel_cfg","kernel_cfg.c"));
        cfg->disableOutput();       //��������λ����ޤǽ��Ϥ����ʤ�

            //����Ū�ʥ��֥������Ȥγ�Ǽ���Ϥ����ǻ��ꤷ�Ƥ���
        cfg->createPart("header")
            .createPart("include")
            .createPart(IDENTIFIER_VARIABLE)
            .createPart(TASK)
            .createPart(SEMAPHORE)
            .createPart(EVENTFLAG)
            .createPart(DATAQUEUE)
            .createPart(MAILBOX)
            .createPart(FIXEDSIZEMEMORYPOOL)
            .createPart(CYCLICHANDLER)
            .createPart(INTERRUPTHANDLER)
            .createPart(EXCEPTIONHANDLER)
            .createPart(INITIALIZER)
            .createPart(OBJECT_INITIALIZER)
            .createPart("others");

            //�����ͥ빽���ե������������٥�Ȥμ¹�
        KernelCfg::CreationEvent ev;
        ev.file = cfg;
        Event<KernelCfg::CreationEvent>::raise(ev);

            //���顼�����å�
        if(ev.file == 0)
            ExceptionMessage("Internal error : kernel_cfg event handler eliminates the instance.","�������顼 : kernel_cfg�Υϥ�ɥ餬���󥹥��󥹤�������") << throwException;
        if(RuntimeObjectTable::getInstance(typeid(KernelCfg)) != ev.file)
            ExceptionMessage("Internal error : kernel_cfg event handler creates the illegal instance.","�������顼 : kernel_cfg�Υϥ�ɥ餬�����ʥ��󥹥��󥹤���������") << throwException;

        return ev.file; //cfg�Ǥϥ���
    }

        //�ե�����̾������Ͳ����Ѥ�̾������������
    string convert_filename_to_definition(string filename)
    {
        string result;
        string::iterator scope;

        scope = filename.begin();
        while(scope != filename.end()) {
            if(isalnum(*scope))
                result += static_cast<char>(toupper(*scope));
            else
                result += '_';
            ++ scope;
        }

        return result;
    }

        //��ưID���շ�̥ե����������
    KernelID * createKernelID(void)
    {
        KernelID * id = 0;

        id = KernelID::createInstance(get_filename("kernel_id","kernel_id.h"));
        id->disableOutput();

            //����Ū�ʥ��֥������Ȥγ�Ǽ���Ϥ����ǻ��ꤷ�Ƥ���
        id-> createPart("__header__")
            .createPart("body")
            .createPart("__footer__");

            //�ե������������٥�Ȥμ¹�
        KernelID::CreationEvent ev;
        ev.file = id;
        Event<KernelID::CreationEvent>::raise(ev);

            //���顼�����å�
        if(ev.file == 0)
            ExceptionMessage("Internal error : kernel_id event handler eliminates the instance.","�������顼 : kernel_id�Υϥ�ɥ餬���󥹥��󥹤�������") << throwException;
        if(RuntimeObjectTable::getInstance(typeid(KernelID)) != ev.file)
            ExceptionMessage("Internal error : kernel_id event handler creates the illegal instance.","�������顼 : kernel_id�Υϥ�ɥ餬�����ʥ��󥹥��󥹤���������") << throwException;

            //¿�ť��󥯥롼�ɲ�����������ɲ�
        string defname = convert_filename_to_definition(id->getFilename());
        id->movePart("__header__");
        (*id)   // << get_agreement(id->getFilename())      //ʸ������Ϳ
                << "#ifndef " << defname << '\n'        //#ifndef KERNELID_H
                << "#define " << defname << "\n\n";     //#define KERNELID_H
        
        id->movePart("__footer__");
        (*id)   << "\n#endif /* " << defname << " */\n\n";          //#endif /* KERNELID_H */

        return ev.file; //id�Ǥϥ���
    }

        //��Ͽ����Ƥ���ʸ���κ���Ĺ������
    unsigned int countLongestSymbolName(const std::map<std::string, int> & identifiers) throw()
    {
        unsigned int max_length = 0;
        std::map<std::string, int>::const_iterator scope;

            // ��äȤ�Ĺ��̾������ĥ���ܥ�̾�򸡺�
        scope = identifiers.begin();
        while(scope != identifiers.end()) {
            if(max_length < scope->first.size())
                max_length = scope->first.size();
            ++ scope;
        }

        return max_length;
    }

        //��ưID���շ�̽��� (����ޤǤȤθߴ��⡼��)
    void serializeIdentifiers_defineStyle(KernelID * out, std::map<std::string, int> & identifier_pool)
    {
        std::map<std::string, int>::const_iterator scope;
        string::size_type max_length;

        (*out) << "\t/* object identifier deifnition */\n\n";

            // ��äȤ�Ĺ��̾������ĥ���ܥ�̾�򸡺�
        max_length = countLongestSymbolName(identifier_pool);

        scope = identifier_pool.begin();
        while(scope != identifier_pool.end()) {
            (*out)  << "#define " << scope->first 
                    << string(max_length - scope->first.size() + 4, ' ')    //�ͤ򤽤���
                    << setw(3)
                    << scope->second << '\n';
            ++ scope;
        }
    }

        //��ưID���շ�̽��� (����ѿ���Ǽ����)
    void serializeIdentifiers_variableStyle(KernelID * id, std::map<std::string, int> & identifier) throw(Exception)
    {
        std::map<std::string, int>::const_iterator scope;
        string::size_type max_length;
        KernelCfg * cfg = getRuntimeObjectInstance(KernelCfg);

            /* kernel_id.h�˽��� */

        (*id) << "#ifdef __cplusplus\n"
                 "#define KERNELID_EXPORT extern \"C\"\n"
                 "#else\n"
                 "#define KERNELID_EXPORT extern\n"
                 "#endif\n\n";

            // ��äȤ�Ĺ��̾������ĥ���ܥ�̾�򸡺�
        max_length = countLongestSymbolName(identifier);

        scope = identifier.begin();
        while(scope != identifier.end()) {
            (*id) << "KERNELID_EXPORT const int "
                  << scope->first
                  << ";\n";

            ++ scope;
        }

        (*id) << "\n#undef KERNELID_EXPORT\n\n";

            /* kernel_cfg.c������������� */

        cfg->movePart(IDENTIFIER_VARIABLE);
        (*cfg) << "\t/* Identifier storage variables */\n";
        scope = identifier.begin();
        while(scope != identifier.end()) {
            (*cfg) << "const int " 
                  << scope->first
                  << string(max_length - scope->first.size() + 4, ' ')
                  << " = "
                  << scope->second << ";\n";
            ++ scope;
        }
    }

        //��ưID���շ�̽��� (ʻ������ - (toppers-dev 28))
    void serializeIdentifiers_blendedStyle(KernelID * id, std::map<std::string, int> & identifier) throw(Exception)
    {
        /* kernel_id.h�ؤν��ϤϽ����Ʊ�� */
        serializeIdentifiers_defineStyle(id, identifier);

            /* kernel_cfg.c������������� */

        std::map<std::string, int>::const_iterator scope;
        string::size_type max_length;
        KernelCfg * cfg = getRuntimeObjectInstance(KernelCfg);

        max_length = countLongestSymbolName(identifier);

        cfg->movePart(IDENTIFIER_VARIABLE);
        (*cfg) << "\t/* Identifier storage variables */\n";
        scope = identifier.begin();
        while(scope != identifier.end()) {
            (*cfg) << "const int " 
                  << scope->first
                  << "_id"
                  << string(max_length - scope->first.size() + 1, ' ')
                  << " = "
                  << scope->second << ";\n";
            ++ scope;
        }
    }

        //��ưID���շ�̤ν���
    void serializeIdentifiers(bool varid_style = false) throw(Exception)
    {
        KernelID * out = getRuntimeObjectInstance(KernelID);
        std::map<std::string, int> identifier_pool;

            //���̻ҥס��������
        {
            Directory * scope = Singleton<Directory>::getInstance()->findChild("/identifier")->getFirstChild();
            while(scope != 0)
            {
                identifier_pool[scope->getKey()] = scope->toInteger();
                scope = scope->getNext();
            }
        }

            //���շ�̤ν���
        out->movePart("body");
        if(varid_style) {
            serializeIdentifiers_blendedStyle(out, identifier_pool);
//            serializeIdentifiers_variableStyle(out, identifier_pool);
        }
        else {
            serializeIdentifiers_defineStyle(out, identifier_pool);
        }

        out->enableOutput();
    }

    void serializeConfiguration_headerPart(KernelCfg & out) throw(Exception)
    {
        const bool backward_compatible = getOptionParameter()["1.3"].isValid();
        
            //Ƭ����ʬ�ν���
        out.movePart("header");

        out // << get_agreement(out.getFilename())          //ʸ����ź��
            << "/* Configured with ["                   //����ե�����졼����󥪥ץ�������Ϥ��Ƥ���
            << getOptionParameter().getCommandLine() 
            << "] */\n\n";

            //1.4�ʹߤ�kernel_cfg.h�����
        if(!backward_compatible)
            out << "#include " << conv_includefile("kernel_cfg.h") << '\n';

            //kernel_id.h��include (kernel_id�ϥ��֥륯�����ȤǤ�����)
        out << "#include \"" << dynamic_cast<KernelID *>(RuntimeObjectTable::getInstance(typeid(KernelID)))->getFilename() <<"\"\n" 
            << '\n';


            //CFG_INT/EXCHDR_ENTRY
            // Q: "<<"�����ä���ʤ��ä��ꤹ��ΤϤʤ�? A: 2���ܤ���5���ܤޤǤ�else�֥�å��ǽ��Ϥ��Ƥ������ƤȤޤä���Ʊ������������Х���ѥ���ˤ�äƤϥ����󥯤���ư�Ĥˤʤ뤷���������Ⱝ���ʤ�ʤ���
        if(backward_compatible) {
            out << "#if TKERNEL_PRVER >= 0x1040\n"
                << "#error \"This configuration file has no compatibility with"
                << " TOPPERS/JSP rel 1.4 or later version.\"\n"
                   "#elif TKERNEL_PRVER >= 0x1011\n"
                << "#define CFG_INTHDR_ENTRY(inthdr) INTHDR_ENTRY(inthdr)\n"
                   "#define CFG_EXCHDR_ENTRY(exchdr) EXCHDR_ENTRY(exchdr)\n"
                   "#define CFG_INT_ENTRY(inthdr) INT_ENTRY(inthdr)\n"
                   "#define CFG_EXC_ENTRY(exchdr) EXC_ENTRY(exchdr)\n"
                << "#else\n"
                << "#define CFG_INTHDR_ENTRY(inthdr) INTHDR_ENTRY(ENTRY(inthdr), inthdr)\n"
                   "#define CFG_EXCHDR_ENTRY(exchdr) EXCHDR_ENTRY(ENTRY(exchdr), exchdr)\n"
                   "#define CFG_INT_ENTRY(inthdr) ENTRY(inthdr)\n"
                   "#define CFG_EXC_ENTRY(exchdr) ENTRY(exchdr)\n"
                << "#endif\n\n";
        }
        else {
            out << "#if TKERNEL_PRVER >= 0x1040\n"
                << "#define CFG_INTHDR_ENTRY(inthdr) INTHDR_ENTRY(inthdr)\n"
                   "#define CFG_EXCHDR_ENTRY(exchdr) EXCHDR_ENTRY(exchdr)\n"
                   "#define CFG_INT_ENTRY(inthdr) INT_ENTRY(inthdr)\n"
                   "#define CFG_EXC_ENTRY(exchdr) EXC_ENTRY(exchdr)\n"
                << "#else\n"
                << "#error \"This configuration file has no compatibility with"
                << " TOPPERS/JSP rel 1.3 or earlier.\"\n"
                << "#endif\n\n";
        }

            //__EMPTY_LABEL�ޥ���ν���
        if(!getOptionParameter()["z"].isValid()) {
            
            string zeromacro;

            if(getOptionParameter()["ZERO"].isValid())
                zeromacro = getOptionParameter()["ZERO"][0];
            else
                zeromacro.assign("x y[0]");

            out <<  "#ifndef __EMPTY_LABEL\n"
                    "#define __EMPTY_LABEL(x,y) " << zeromacro << "\n"
                    "#endif\n\n";
        }

            /* PRID�Υ����å� */
        out << "#if TKERNEL_PRID != 0x0001u /* TOPPERS/JSP */\n"
               "#error \"You can not use this configuration file without TOPPERS/JSP\"\n"
               "#endif\n\n";
    }
}

void ConfigurationFileGenerator::parseOption(Directory & parameter)
{
    string work;

    if(findOption("h","help"))
    {
        cerr << endl << Message(
            "Kernel configuration file generator\n"
            "  -id, --kernel_id=filename  : Specify the name of ID assignment file\n"
            "  -cfg,--kernel_cfg=filename : Specify the name of kernel configuration file\n"
            "  -il, --include-libstyle    : Use #include <...> style for kernel headers\n"
            "  -oproto, --output-prototype: Output task prototype definitions in kernel_cfg\n"
            "  -z, --nonzero              : Do not output __EMPTY_LABEL macro and related definitions\n"
            "  -1.3  : Generates kernel_cfg.c for TOPPERS/JSP rel 1.3\n",
            "�����ͥ빽���ե����������\n"
            "  -id, --kernel_id=�ե�����̾  : ID�����ե������̾������ꤷ�ޤ�\n"
            "  -cfg,--kernel_cfg=�ե�����̾ : �����ͥ빽���ե������̾������ꤷ�ޤ�\n"
            "  -il, --include-libstyle      : �����ͥ�Υإå��ե������<...>�η��ǽ��Ϥ��ޤ�\n"
            "  -oproto, --output-prototype  : ���������Τʤɤ������kernel_cfg.c���������ޤ�\n"
            "  -z, --nonzero                : __EMPTY_LABEL�ޥ���λ��Ѥ����¤��ޤ�\n"
            "  -1.3  : TOPPERS/JSP rel 1.3 �ѤΥ���ե�����졼�����ե�������������ޤ�\n");
        return;
    }

    checkOption("cfg","cfg");
    checkOption("id","id");

        /*
         *  �����ͥ륳��ե�����졼������̤Υե����� (kernel_cfg.c) �ν������
         */

    createKernelCfg();

        /*
         *  ID���շ�̤Υե����� (kernel_id.h) �ν������
         */

    createKernelID();

        /* ����¾���ץ���� */
    restrict_zero = findOption("z","zero");
    def_prototype = findOption("oproto","output-prototype");
    libstyle_include = findOption("il","include-libstyle");
    backward_compatible = findOption("1.3","1.3");
    
    checkOption("mcfg","minimize-cfg");
    checkOption("ZERO","ZERO");
    checkOption("obj", "dump-object");
    checkOption("ext");

    activateComponent();
}

void ConfigurationFileGenerator::onFatalExit(Directory & container)
{
        //�㳰�ǰ۾ｪλ�����顢�ե�������������ʤ�
    dynamic_cast<MultipartStream *>(RuntimeObjectTable::getInstance(typeid(KernelCfg)))->disableOutput();
    dynamic_cast<MultipartStream *>(RuntimeObjectTable::getInstance(typeid(KernelID)))->disableOutput();
}

void ConfigurationFileGenerator::createObjectDefinition(MultipartStream * out, Directory & container, int flag, ...)
{
    Directory * scope;
    const char * buffer;
    string work;

    map<int, Directory *> sorter;
    map<int, Directory *>::iterator psorter;

    va_list vl;
    int i;

    Directory & id = container[string(PREFIX "/") + container.getKey().c_str()];

    if(container.size() == 0 && findOption("mcfg","minimize-cfg"))
    {
        if(!getOptionParameter().find("ext"))
            ExceptionMessage("Use of the extended option --minimize-cfg. Please use -ext option together.","--minimize���ץ����ϳ�ĥ��ǽ�Ǥ������Ѥ���ˤ�-ext����ꤷ�Ƥ���������").throwException();
        return;
    }
    va_start(vl, flag);


        //ɬ�פʾ���κ���
    work = string(va_arg(vl, const char *));
    id["id"]  = work;
    transform(work.begin(), work.end(), work.begin(), toupper_function);
    id["ID"]  = work;
    

    if((flag & SHORT_ID) != 0)
    {
        work = string(va_arg(vl, const char *));
        id["sid"]  = work;
	for(i=0; i<(signed)work.size(); i++) {
	  if (work[i] >= 'a' && work[i] <= 'z')
	    work[i] = work[i] - 'a' + 'A';
	}
        id["SID"]  = work;
    }else
    {
        id["sid"] = id["id"].toString();
        id["SID"] = id["ID"].toString();
    }

    if(!backward_compatible)
        id["symbolprefix"] = "_kernel_";

    work = container.getKey();
    id["name"] = work;
    out->movePart(work);

        //���֥������Ƚ�����ؿ����ɲ�
    if((flag & INIT) != 0 && container.size() != 0)
        container["/" OBJECT_INITIALIZER].addChild(new Directory(work));

    (*out) << "\n\t/* " << (Message("Object initializer [%]","���֥������Ƚ�����֥�å� [%]") << work) << " */\n\n";

    if(((flag & HEADER) != 0) && backward_compatible)
        (*out) << "#include " << conv_includefile(work) << "\n\n";

    if((flag & TNUM) != 0)
    {
        (*out) << id.format("#define TNUM_$(ID)ID ") << container.size() << "\n\n";
        (*out) << id.format("const ID $(symbolprefix,)tmax_$(id)id = (TMIN_$(ID)ID + TNUM_$(ID)ID - 1);\n\n");
    }

    if((flag & TNUMNO) != 0)
    {
        (*out) << id.format("#define TNUM_$(ID)NO ") << container.size() << "\n\n";
        (*out) << id.format("const UINT $(symbolprefix,)tnum_$(id)no = TNUM_$(ID)NO;\n\n");
    }

        /* ID��˥����� (���λ�����Ϣ�֤����ꤷ�Ƥ���Ϥ��ʤΤǡ������å��Ϥ��ʤ�) */
    if((flag & (BUFFER|DEFINITION)) != 0)
    {
        const bool is_identifier = (flag & TNUMNO) == 0;

        i = 0;
        scope = container.getFirstChild();
        while(scope != 0)
        {
            if(is_identifier)
                sorter[scope->toInteger(i++)] = scope;
            else
                sorter[i++] = scope;

            scope = scope->getNext();
        }
    }

        //�ץ�ȥ���������ν���
    if((flag & PROTOTYPE) != 0)
    {
        buffer = va_arg(vl, const char *);

        if(def_prototype)
        {
            set<string> func;
            set<string>::iterator pfunc;

            scope = container.getFirstChild();
            while(scope != NULL)
            {
                func.insert(scope->format(buffer));
                scope = scope->getNext();
            }

            pfunc = func.begin();
            while(pfunc != func.end())
            {
                (*out) << (*pfunc) << '\n';
                ++ pfunc;
            }
        }
    }

        //�Хåե��κ���
    if((flag & BUFFER) != 0 && container.size() != 0)
    {
        buffer = va_arg(vl, const char *);
        psorter = sorter.begin();
        while(psorter != sorter.end())
        {
            (*out) << (*psorter).second->format(buffer) << '\n';
            ++ psorter;
        }
        (*out) << '\n';
    }

        //����֥�å�(xINIB)�ν���
    if((flag & DEFINITION) != 0)
    {
        buffer = va_arg(vl, const char *);
        if(container.size() != 0)
        {
            (*out) << id.format("const $(SID)INIB $(symbolprefix,)$(sid)inib_table[TNUM_$(ID)") << ( (flag & TNUMNO) != 0  ? "NO" : "ID") << "] = {\n";
            psorter = sorter.begin();
            while(psorter != sorter.end())
            {
                (*out) << "\t{" << (*psorter).second->format(buffer) << '}';
                ++ psorter;
                if(psorter != sorter.end())
                    (*out) << ',';
                (*out) << '\n';
            }
            (*out) << "};\n\n";
        }else
            if( !restrict_zero )
                (*out) << id.format("__EMPTY_LABEL(const $(SID)INIB, $(symbolprefix,)$(sid)inib_table);\n");
    }

    if((flag & INITLIST) != 0)
    {
        Directory * node;

            /* ������ID�ֹ�򥽡��� */
        sorter.clear();
        node = container.getFirstChild();
        while(node != NULL)
        {
            sorter.insert(pair<int,Directory*>(node->findChild("#order")->toInteger(), node));
            node = node->getNext();
        }

        *out << id.format("const ID $(symbolprefix,)$(sid)order_table[TNUM_$(ID)ID] = {");
        psorter = sorter.begin();
        while(psorter != sorter.end())
        {
            *out << psorter->second->toInteger();
            ++ psorter;
            if(psorter != sorter.end())
                *out << ',';
        }
        *out << "};\n\n";
    }

        //����֥�å�(xCB)�ν���
    if((flag & CONTROLBLOCK) != 0)
    {
        if(container.size() != 0)
            (*out) << id.format("$(SID)CB $(symbolprefix,)$(sid)cb_table[TNUM_$(ID)ID];\n\n");
        else
            if( !restrict_zero )
                (*out) << id.format("__EMPTY_LABEL($(SID)CB, $(symbolprefix,)$(sid)cb_table);\n\n");
    }
}

void ConfigurationFileGenerator::body(Directory & container)
{
    Directory * scope;
    KernelCfg * out;
    string work;
    const bool varid_style = findOption("var","variable-id");

        /* kernel_id.h�ν��� */
    serializeIdentifiers(varid_style);

        /* kernel_cfg.c�ν��� */
    out = dynamic_cast<KernelCfg *>(RuntimeObjectTable::getInstance(typeid(KernelCfg)));
    if(out == 0) {
        ExceptionMessage("[Internal error] The stream buffer of kernel_cfg disappeared.","[�������顼] �ե����륹�ȥ꡼�ब�����ޤ��� (kernel_cfg.c)").throwException();
        return;
    }

        /* Ƭ�������ʬ�κ��� */
    serializeConfiguration_headerPart(*out);

        /* INCLUDE */
    out->movePart(INCLUDEFILE);
    scope = container(OBJECTTREE "/" INCLUDEFILE)->getFirstChild();
    (*out) << "\t/* " << Message("User specified include files","�桼������Υ��󥯥롼�ɥե�����") << "*/\n";
    while(scope != 0)
    {
        (*out) << "#include " << scope->toString() << '\n';
        scope = scope->getNext();
    }
    (*out) << '\n';

        /* TASK */
    work.assign("$(tskatr), (VP_INT)($(exinf)), (FP)($(task)), INT_PRIORITY($(itskpri)), __TROUND_STK_UNIT($(stksz)), __stack_$@, $(texatr), (FP)($(texrtn))");
    if(container["/cpu"].toString().compare("nios32") == 0)
        work += ", $(hi_limit), $(lo_limit)";
    createObjectDefinition(out, container[OBJECTTREE "/" TASK], HEADER|TNUM|SHORT_ID|BUFFER|DEFINITION|CONTROLBLOCK|INIT|PROTOTYPE|INITLIST,"tsk", "t", "void $(task)(VP_INT exinf);", "static __STK_UNIT __stack_$@[__TCOUNT_STK_UNIT($(stksz))];",work.c_str());

        /* SEMAPHORE */
    createObjectDefinition(out, container[OBJECTTREE "/" SEMAPHORE], HEADER|TNUM|DEFINITION|CONTROLBLOCK|INIT,"sem", "$(sematr), $(isemcnt), $(maxsem)");

        /* EVENTFLAG */
    createObjectDefinition(out, container[OBJECTTREE "/" EVENTFLAG], HEADER|TNUM|DEFINITION|CONTROLBLOCK|INIT,"flg", "$(flgatr), $(iflgptn)");

        /* DATAQUEUE */
    createObjectDefinition(out, container[OBJECTTREE "/" DATAQUEUE], HEADER|TNUM|BUFFER|DEFINITION|CONTROLBLOCK|INIT,"dtq", "#if ($(dtqcnt)) > 0\n  static VP_INT __dataqueue_$@[$(dtqcnt)];\n#else\n  #define __dataqueue_$@ NULL\n#endif","$(dtqatr), $(dtqcnt), __dataqueue_$@");

        /* MAILBOX */
    createObjectDefinition(out, container[OBJECTTREE "/" MAILBOX], HEADER|TNUM|DEFINITION|CONTROLBLOCK|INIT,"mbx","$(mbxatr), $(maxmpri)");

        /* FIXEDSIZEMEMORYPOOL */
    createObjectDefinition(out, container[OBJECTTREE "/" FIXEDSIZEMEMORYPOOL], HEADER|TNUM|BUFFER|DEFINITION|CONTROLBLOCK|INIT,"mpf","static __MPF_UNIT __fixedsize_memorypool_$@[__TCOUNT_MPF_UNIT($(blksz)) * (($(blkcnt)))];","$(mpfatr), __TROUND_MPF_UNIT($(blksz)), __fixedsize_memorypool_$@, (VP)((VB *)__fixedsize_memorypool_$@ + sizeof(__fixedsize_memorypool_$@))");

        /* CYCLICHANDLER */
    createObjectDefinition(out, container[OBJECTTREE "/" CYCLICHANDLER], HEADER|TNUM|DEFINITION|CONTROLBLOCK|INIT|PROTOTYPE,"cyc","void $(cychdr)(VP_INT exinf);","$(cycatr),$(exinf),(FP)($(cychdr)),$(cyctim),$(cycphs)");

        /* INTERRUPTHANDLER */
    createObjectDefinition(out, container[OBJECTTREE "/" INTERRUPTHANDLER], HEADER|BUFFER|TNUMNO|DEFINITION|INIT|PROTOTYPE,"inh","void $(inthdr)(void);","CFG_INTHDR_ENTRY($(inthdr));","$@,$(inhatr),(FP)CFG_INT_ENTRY($(inthdr))");

        /* EXCEPTIONHANDLER */
    createObjectDefinition(out, container[OBJECTTREE "/" EXCEPTIONHANDLER], HEADER|BUFFER|TNUMNO|DEFINITION|INIT|PROTOTYPE,"exc","void $(exchdr)(VP p_excinf);","CFG_EXCHDR_ENTRY($(exchdr));","$@,$(excatr),(FP)CFG_EXC_ENTRY($(exchdr))");


        /* ���֥������Ƚ�����롼���� */
    out->movePart(OBJECT_INITIALIZER);
    (*out) << "\t/* " << Message("Object initialization routine","���֥������Ƚ�����롼����") << " */\n\n";
    (*out) << "void\n" << conv_kernelobject("object_initialize") << "(void)\n{\n";
    scope = container["/" OBJECT_INITIALIZER].getFirstChild();
    while(scope != 0)
    {
        (*out) << '\t' << conv_kernelobject(scope->toString() + "_initialize") << "();\n";
        scope = scope->getNext();
    }
    (*out) << "}\n\n";


        /* ������ϥ�ɥ� */
    out->movePart(INITIALIZER);
    (*out) << "\t/* " << Message("Initialization handler","������ϥ�ɥ鵯ư�롼����") << " */\n\n";
    (*out) << "void\n" << conv_kernelobject("call_inirtn") << "(void)\n{\n";
    scope = container[OBJECTTREE "/" INITIALIZER].getFirstChild();
    while(scope != 0)
    {
        (*out) << scope->format("\t$(inirtn)( (VP_INT)($(exinf)) );\n");
        scope = scope->getNext();
    }
    (*out) << "}\n\n";

        /* ��λ�ϥ�ɥ� */
    scope = container[OBJECTTREE "/"  TERMINATOR].getLastChild();
    if(!backward_compatible) {
        (*out) << "void\n" << conv_kernelobject("call_terrtn") << "(void)\n{\n";
        while(scope != 0)
        {
            (*out) << scope->format("\t$(terrtn)( (VP_INT)($(exinf)) );\n");
            scope = scope->getPrev();
        }
        (*out) << "}\n\n";
    }
    else {
        if(scope->size() != 0)
            ExceptionMessage("VATT_TER is not supported for TOPPERS/JSP rel 1.3 or earlier.",
                             "VATT_TER��TOPPERS/JSP rel 1.3�����Ǥϥ��ݡ��Ȥ���ޤ���").throwException();
    }

    out->movePart("others");
    (*out) << "TMEVTN   " << conv_kernelobject("tmevt_heap") << "[TNUM_TSKID + TNUM_CYCID];\n\n";

    container["/object_initializer"].erase();

    string filename;
    if(findOption("obj","dump-object",&filename))
    {
        if(filename.empty())
            filename.assign("kernel_obj.dat");

        fstream f(filename.c_str(),ios::out|ios::binary);
        if(f.is_open())
        {
            container[OBJECTTREE].Store(&f);
            f.close();
        }else
            ExceptionMessage(" Failed to open the file % for storing object definitions"," ���֥������Ⱦ�����Ǽ���뤿��Υե�����(%)�������ޤ���") << filename << throwException;
    }

    out->enableOutput();
}


/* ======================================================================== */

