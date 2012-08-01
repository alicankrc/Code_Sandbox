#include "TACID.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

static int str2int( string const& input ){
    int out;
    stringstream(input) >> out;
    return out;
}

namespace GEO{
namespace GS2{

    string months[] = {"NONE","JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC"};
   
    /** TACID Default Constructor */
    TACID::TACID(){
        day = "00";
        month = "NON";
        year = "00";
        program_code = "2Z";
        filename = "_NONE_SELECTED_";
        sortie_number = "00";
    }

    /** TACID Parameterized Constructor */
    TACID::TACID( std::string const& tacid ){
       
        int pos = 0;
        int len = 2;
        //set the filename
        filename = tacid;
        
        //set the day (Acquisition Date)
        day   = tacid.substr(pos,len);
        
        //set the month (Acquisition Date)
        pos += len;
        len = 3;
        month = tacid.substr(pos,len);
        
        //set the year (Acquisition Date)
        pos += len;
        len = 2;
        year = tacid.substr(pos,len);
        
        //set the Program Code
        pos += len;
        len = 2;
        program_code = tacid.substr(pos,len);

        //set the sortie number
        pos += len;
        len = 2;
        sortie_number = tacid.substr(pos,len);
        
        //set the scene number
        pos += len;
        len = 5;
        scene_number  = tacid.substr(pos,len);
        
        //set DoD producer code
        pos += len;
        len = 2;
		producer_code = tacid.substr(pos,len);

		//set product number
        pos += len;
        len = 6;
		product_number = tacid.substr(pos,len);
		
		//set the NGA Project Code
        pos += len;
        len = 2;
		project_code = tacid.substr(pos,len);

		//set the replay (reprocessed or retransmitted state flag)
		pos += len;
        len = 3;
        replay_code = tacid.substr(pos,len);
		
        //set the producer serial number
        pos += len;
        len = 3;
		producer_sn = tacid.substr(pos,len);
	
		//set the production datim
        pos += len;
        len = 8;
		production_datim = tacid.substr(pos,len);
    
    }

    /**
     * Output the TACID to a filename
    */
    string TACID::toString()const{

        return ( day
               + month
               + year
               + program_code
               + sortie_number
               + scene_number
               + producer_code
               + product_number
      	       + project_code
               + replay_code
		       + producer_sn
		       + production_datim
               + string(".ntf"));
    }
        



    ostream& operator << ( ostream& ostr, const TACID& tacid ){

        ostr << "TACID: " << endl;
        ostr << "     Filename        : " << tacid.filename << endl;
        ostr << "     Acq Date        : " << tacid.day << tacid.month << tacid.year << endl;
        ostr << "     Prog Code       : " << tacid.program_code << endl;
        ostr << "     Sortie Number   : " << tacid.sortie_number << endl;
        ostr << "     Scene Number    : " << tacid.scene_number << endl;
        ostr << "     Producer Code   : " << tacid.producer_code << endl;
        ostr << "     Product Number  : " << tacid.product_number << endl;
        ostr << "     Project Code    : " << tacid.project_code << endl;
        ostr << "     Replay Code     : " << tacid.replay_code << endl;
        ostr << "     Producer SN     : " << tacid.producer_sn << endl;
        ostr << "     Production DATIM: " << tacid.production_datim << endl;
        return ostr;
    }


    /** Check to make sure that a TACID is valie */    
    bool TACID::isValidTACID( const std::string& tacid ){
        
        //check size
        if( tacid.size() != 44 && tacid.size() != 40 ) return false;
        
        //check month
        bool mon_set = false;
        for( size_t i=1; i<=12; i++)
            if( tacid.substr(2,3) == months [i] ){
                mon_set = true;
                break;
            }
        if( mon_set != true ) return false;
        


        return true;
    }


}// end of GS2 Namespace
}// end of GEO Namespace

