#ifndef __SRC_OPTIONS_HPP__
#define __SRC_OPTIONS_HPP__

///STL Libraries
#include <iostream>
#include <string>

///Personal Libraries
#include "Parser.hpp"

///useful includes
using namespace std;


/** 
 * Useful enumerations
*/
const int CAMERA_EO = 0;
const int CAMERA_IR = 1;


/**
 * @class Options
 *
 * The required configuration parameters for the program.
*/
class Options{

    public:
        
        /**
         * Parameterized Constructor
        */
        Options( const int argc, char** argv );
        

        /** 
         * Print the current configuration
         * NOTE: For debugging only
        */
        void print()const;
        
        /**
         * Print the help menu
        */
        void usage();
        

    
        string status_filename; /*< Name of the file which manages the program state */
        string config_filename; /*< Name of the configuration file */
            
        string camera_type;     /*< Type of camera we are using */
            
        PSR::Parser parser;          /*<  Configuration file parser  */


        string input_base;      /*< Base directory to search for cameras */
        string collect_name;    /*< Name of the collect */

        int number_eo_frames;   /*< Number of eo frames per step  */
        int number_ir_frames;   /*< Number of ir frames per step  */


};


#endif