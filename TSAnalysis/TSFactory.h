#ifndef _TS_FACTORY_H_
#define _TS_FACTORY_H_

#include "../def.h"
#include "../Section/Section.h"
#include "../Section/PSI_SI/BAT.h"
#include "../Section/PSI_SI/CAT.h"
#include "../Section/PSI_SI/EIT.h"
#include "../Section/PSI_SI/NIT.h"
#include "../Section/PSI_SI/PAT.h"
#include "../Section/PSI_SI/PMT.h"
#include "../Section/PSI_SI/SDT.h"
#include "../Section/PSI_SI/TDT.h"
#include "../Section/PSI_SI/TOT.h"
#include "../Section/DSMCC/DsmccSection.h"   

class TSData;

class TSFactory
{
public:

    bool addSection(Section* section);
    virtual Section* createSectoin(TSData* raw_section);
    static TSFactory* GetInstance();
    void TSGather(int pid, uint8_t* ts_packet);
    void ESGather(int pid, uint8_t* ts_packet, std::ofstream& of);
    
    PAT* pat;
    std::set<PMT*, cmp_secp<PMT>> pmt_list;
    std::set<NIT*, cmp_secp<NIT>> nit_list;
    std::set<CAT*, cmp_secp<CAT>> cat_list;
    std::list<BAT*> bat_list;
    std::set<SDT*, cmp_secp<SDT>> sdt_list;
    std::set<EIT*, cmp_secp<EIT>> eit_list;
    TDT* tdt;
    TOT* tot;
    std::list<ESGInfo*> esg_list; 
    std::list<ESGInfo*> esg_stable_list;

    TSData* raw_sarr[MAX_PID_NUM];

    std::list<Program*> prog_list;
    uint32_t pkt_idx;

private:
    TSFactory();
    TSFactory(const TSFactory&);
    TSFactory& operator=(const TSFactory&);
    ~TSFactory();

    int adaptationFieldAnalysis(uint8_t* ts_packet, TSData* raw_ts,
                                bool& pcr_inv_err, bool& pcr_dis_err, bool& pcr_acu_err);
    bool continuityCheck(uint8_t* ts_packet, TSData* raw_ts, bool& cc_err);
    void SectionAnalysis(TSData* raw_ts);
    void PESAnalysis(TSData* raw_ts);

    static TSFactory* _instance;
};



#endif 
