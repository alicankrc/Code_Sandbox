#ifndef __SRC_COORDINATES_LATLONCOORD_H__
#define __SRC_COORDINATES_LATLONCOORD_H__

#include <string>

#ifdef DEPLOYED
#include <geoimage/coordinates/Datum.hpp>
#include <geoimage/io/IO_Configuration.hpp>
#else
#include "Datum.hpp"
#include "../io/IO_Configuration.hpp"
#endif

#if USE_OPENCV == 1
#include <opencv2/core/core.hpp>
#endif


namespace GEO{

class CoordinateLatLon{

    public:
        
        /** 
         * CoordinateLatLon Constructor 
        */
        CoordinateLatLon();
        
        /**
         * Decimal Degree Constructor 
         *
         * @param[in] latDD Latitude  in Decimal Degree Format
         * @param[in] lonDD Longitude in Decimal Degree Format
        */
        CoordinateLatLon( const double& latDD, const double& lonDD, const double& _elevation = 0, std::string const& dat = "WGS84" );
        
        /**
         * OpenCV Point Constructor 
         *
         * @param[in] coord OpenCV Coordinate
        */
        CoordinateLatLon( const cv::Point2f& coord, const double& _elevation, std::string const& dat = "WGS84" );
        
        /**
         * OpenCV Point Constructor
         *
         * @param[in] coord OpenCV Coordinate
        */
        CoordinateLatLon( const cv::Point3f& coord, std::string const& dat = "WGS84" );
        
        /**
         * Lat Lon Coordinate in Degree, Minutes Format
         *
         * @param[in] latDeg Latitude Degree Component
         * @param[in] latMin Latitude Minutes Component
         * @param[in] lonDeg Longitude Degree Component
         * @param[in] lonMin Longitude Minutes Component
        */
        CoordinateLatLon( const int& latDeg, const double& latMin, 
                          const int& lonDeg, const double& lonMin,
                          const double& _elevation = 0,
                          std::string const& _datum = "WGS84" );
        
        /**
         * Lat Lon Coordinate in Degree, Minutes Format
         *
         * @param[in] latDeg Latitude  Degree  Component
         * @param[in] latMin Latitude  Minutes Component
         * @param[in] latSec Latitude  Seconds Component
         * @param[in] lonDeg Longitude Degree  Component
         * @param[in] lonMin Longitude Minutes Component
         * @param[in] lonSec Longitude Seconds Component
        */
        CoordinateLatLon( const int& latDeg, const int&  latMin, const double& latSec,
                          const int& lonDeg, const int&  lonMin, const double& lonSec,
                          const double& _elevation = 0,
                          std::string const& _datum = "WGS84" );

        
        
        /** 
          * Convert the Coordinate into a readable string 
        */
        std::string toString()const;
        
#if USE_OPENCV == 1

        /**
         * Convert the Coordinate into an OpenCV Point
        */
        cv::Point2f toPoint2f( )const;

        /**
         * Convert the Coordinate into an OpenCV Point
        */
        cv::Point3f toPoint3f( )const;
#endif

        double lat;        /*< Latitude               */
        double lon;        /*< Longitude              */
        double elevation;  /*< Meters above sea level */
        
        std::string datum; /*< Datum     */
};

}// end of GEO namespace 

#endif