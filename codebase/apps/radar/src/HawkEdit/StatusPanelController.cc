// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* 
// ** Copyright UCAR (c) 1990 - 2016                                         
// ** University Corporation for Atmospheric Research (UCAR)                 
// ** National Center for Atmospheric Research (NCAR)                        
// ** Boulder, Colorado, USA                                                 
// ** BSD licence applies - redistribution and use in source and binary      
// ** forms, with or without modification, are permitted provided that       
// ** the following conditions are met:                                      
// ** 1) If the software is modified to produce derivative works,            
// ** such modified software should be clearly marked, so as not             
// ** to confuse it with the version available from UCAR.                    
// ** 2) Redistributions of source code must retain the above copyright      
// ** notice, this list of conditions and the following disclaimer.          
// ** 3) Redistributions in binary form must reproduce the above copyright   
// ** notice, this list of conditions and the following disclaimer in the    
// ** documentation and/or other materials provided with the distribution.   
// ** 4) Neither the name of UCAR nor the names of its contributors,         
// ** if any, may be used to endorse or promote products derived from        
// ** this software without specific prior written permission.               
// ** DISCLAIMER: THIS SOFTWARE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS  
// ** OR IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED      
// ** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.    
// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* 
///////////////////////////////////////////////////////////////
// StatusPanel.cc
//
// Status Panel object
//
// Brenda Javornik, EOL, NCAR, P.O.Box 3000, Boulder, CO, 80307-3000, USA
//
// June 2023
//
///////////////////////////////////////////////////////////////
//
// StatusPanel manages the metadata displayed on the left-hand side
// of the Polar display
//
///////////////////////////////////////////////////////////////

#include "StatusPanelController.hh"
#include "DisplayField.hh"
#include "FieldListView.hh"
#include "Params.hh"
#include "Reader.hh"
#include "AllocCheck.hh"
#include "DataModel.hh"

#include <string>
#include <cmath>
#include <iostream>
#include <algorithm>    // std::find
#include <unordered_map>
#include <Ncxx/H5x.hh>
#include <QActionGroup>
#include <QApplication>
#include <QButtonGroup>
#include <QDialogButtonBox>
#include <QDir>
#include <QFrame>
#include <QFont>
#include <QLabel>
#include <QToolTip>
#include <QMenu>
#include <QMenuBar>
#include <QGroupBox>
#include <QMessageBox>
#include <QFormLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QListWidgetItem>
#include <QStringListModel>
#include <QRadioButton>
#include <QStatusBar>
#include <QDateTime>
#include <QDateTimeEdit>
#include <QLineEdit>
#include <QErrorMessage>
#include <QFileDialog>
#include <QSlider>
#include <QGraphicsScene>
#include <QGraphicsAnchorLayout>
#include <QGraphicsProxyWidget>

#include <cstdlib>
#include <fstream>
#include <toolsa/toolsa_macros.h>
#include <toolsa/pmu.h>
#include <toolsa/file_io.h>
#include <toolsa/DateTime.hh>
#include <toolsa/LogStream.hh>
#include <dsserver/DsLdataInfo.hh>
#include <radar/RadarComplex.hh>
#include <Radx/RadxFile.hh>
#include <Radx/NcfRadxFile.hh>
#include <Radx/RadxSweep.hh>
#include <Radx/RadxField.hh>
#include <Radx/RadxTime.hh>
#include <Radx/RadxPath.hh>

#include <toolsa/toolsa_macros.h>
#include <toolsa/Path.hh>

#include "CloseEventFilter.hh"
using namespace std;
//using namespace H5x;

// Constructor


StatusPanelController::StatusPanelController(StatusPanelView *view)
{
  _view = view;
}

// destructor

StatusPanelController::~StatusPanelController()
{
  cerr << "StatusPanel destructor called " << endl;
}

void StatusPanelController::setDisplay(
    bool show_fixed_angle,
    bool show_volume_number,
    bool show_sweep_number,
    bool show_n_samples,
    bool show_n_gates,
    bool show_gate_length,
    bool show_pulse_width,
    bool show_prf_mode,
    bool show_prf,
    bool show_nyquist,
    bool show_max_range,
    bool show_unambiguous_range,
    bool show_measured_power_h,
    bool show_measured_power_v,
    bool show_scan_name,
    bool show_scan_mode,
    bool show_polarization_mode,
    bool show_latitude,
    bool show_longitude,
    bool show_altitude,
    bool show_altitude_rate,
    bool show_speed,
    bool show_heading,
    bool show_track,
    bool show_sun_elevation,
    bool show_sun_azimuth) {

    _show_fixed_angle = show_fixed_angle;
    _show_volume_number = show_volume_number;
    _show_sweep_number = show_sweep_number;
    _show_n_samples = show_n_samples;
    _show_n_gates = show_n_gates;
    _show_gate_length = show_gate_length;
    _show_pulse_width = show_pulse_width;
    _show_prf_mode = show_prf_mode;
    _show_prf = show_prf;
    _show_nyquist = show_nyquist;
    _show_max_range = show_max_range;
    _show_unambiguous_range = show_unambiguous_range;
    _show_measured_power_h = show_measured_power_h;
    _show_measured_power_v = show_measured_power_v;
    _show_scan_name = show_scan_name;
    _show_scan_mode = show_scan_mode;
    _show_polarization_mode = show_polarization_mode;
    _show_latitude = show_latitude;
    _show_longitude = show_longitude;
    _show_altitude = show_altitude;
    _show_altitude_rate = show_altitude_rate;
    _show_speed = show_speed;
    _show_heading = show_heading;
    _show_track = show_track;
    _show_sun_elevation = show_sun_elevation;
    _show_sun_azimuth = show_sun_azimuth;
}


void StatusPanelController::createStatusPanel() {

//  _elevVal = _createStatusVal("Elev", "-99.99", row++, fsize2);
//  _azVal = _createStatusVal("Az", "-999.99", row++, fsize2);

  if (_show_fixed_angle) {
    _view->create(StatusPanelView::FixedAngleKey);
  }
  
  if (_show_volume_number) {
    _view->create(StatusPanelView::VolumeNumberKey);
  }
  
  if (_show_sweep_number) {
    _view->create(StatusPanelView::SweepNumberKey);
  }
  
  if (_show_n_samples) {
    _view->create(StatusPanelView::NSamplesKey);
  }

  if (_show_n_gates) {
    _view->create(StatusPanelView::NGatesKey);
  }
  
  if (_show_gate_length) {
    _view->create(StatusPanelView::GateSpacingKey);
  }
  
  
  if (_show_pulse_width) {
    _view->create(StatusPanelView::PulseWidthKey);
  }

  if (_show_prf_mode) {
    _view->create(StatusPanelView::PrfModeKey);
  }

  if (_show_prf) {
    _view->create(StatusPanelView::PrfKey);
  }

  if (_show_nyquist) {
    _view->create(StatusPanelView::NyquistKey);
  }

  if (_show_max_range) {
    _view->create(StatusPanelView::MaxRangeKey);
  }

  if (_show_unambiguous_range) {
    _view->create(StatusPanelView::UnambiguousRangeKey);
  }

  if (_show_measured_power_h) {
    _view->create(StatusPanelView::PowerHKey);
  }

  if (_show_measured_power_v) {
    _view->create(StatusPanelView::PowerVKey);
  }

  if (_show_scan_name) {
    _view->create(StatusPanelView::ScanNameKey);
  }

  if (_show_scan_mode) {
    _view->create(StatusPanelView::SweepModeKey);
  }

  if (_show_polarization_mode) {
    _view->create(StatusPanelView::PolarizationModeKey);
  }

  if (_show_latitude) {
    _view->create(StatusPanelView::LatitudeKey);
  }

  if (_show_longitude) {
    _view->create(StatusPanelView::LongitudeKey);
  }

  if (_show_altitude) {
    if (_altitudeInFeet) {
      _view->create(StatusPanelView::AltitudeInFeetKey);
    } else {
      _view->create(StatusPanelView::AltitudeInKmKey);
    }
  }

  if (_show_altitude_rate) {
    if (_altitudeInFeet) {
      _view->create(StatusPanelView::AltitudeRateFtsKey);
    } else {
      _view->create(StatusPanelView::AltitudeRateMsKey);
    }
  }

  if (_show_speed) {
    _view->create(StatusPanelView::SpeedKey);
  }

  if (_show_heading) {
    _view->create(StatusPanelView::HeadingKey);
  }

  if (_show_track) {
    _view->create(StatusPanelView::TrackKey);
  }

  if (_show_sun_elevation) {
    _view->create(StatusPanelView::SunElevationKey);
  }

  if (_show_sun_azimuth) {
    _view->create(StatusPanelView::SunAzimuthKey);
  }

  _view->createGeoreferenceLabels();

  _view->show();

}

void StatusPanelController::setRadarName(string radarName, string siteName) {
  _view->setRadarName(radarName, siteName);
};

void StatusPanelController::createDateTime() {
  _view->createDateTime();
}

// ??? the push should NOT come from the PolarManager;
// the pull of information should come from the view via the controller!!!
// PolarManager emits event
// StatusPanelController listens for the event and calls the _view action
// StatusPanelView emits request for info for row,column???
// StatusPanelView getValue (row, column) of table view.
void StatusPanelController::updateStatusPanel(const RadxRay *ray) {

  if (ray == NULL) 
    return;

  DateTime rayTime(ray->getTimeSecs());
  //sprintf(text, "%.4d/%.2d/%.2d",
  //        rayTime.getYear(), rayTime.getMonth(), rayTime.getDay());

  //sprintf(text, "%.2d:%.2d:%.2d.%.3d",
  //        rayTime.getHour(), rayTime.getMin(), rayTime.getSec(),
  //        ((int) ray->getNanoSecs() / 1000000));

  _view->setDateTime(rayTime.getYear(), rayTime.getMonth(), rayTime.getDay(),
    rayTime.getHour(), rayTime.getMin(), rayTime.getSec(),
    ray->getNanoSecs());

  _view->updateAzEl(ray->getAzimuthDeg(), ray->getElevationDeg());

  //if (_fixedAngVal) {  
  //  _setText(text, "%6.2f", ray->getFixedAngleDeg());
  //  _fixedAngVal->setText(text);
  //}

  //   _view->set(<key>, <value>) // one for int, one for float, one for string.
  //values.setSet(nDisplayValues);

  // we now have a hash/unordered_map of all the values to display
  // if we can just go through the unordered_map systematically, and
  // know which ray value is associated, then we don't need all the if
  // statements.

  // go through the unordered_map and use a case statement on the Keys?
  // to associate the ray variable?

  const RadxGeoref *georef = ray->getGeoreference();

  const StatusPanelView::Hashy myHashy = _view->getMetaDataMap();
  StatusPanelView::HashyConstIt it;
  for (it=myHashy.begin(); it != myHashy.end(); ++it) {
    int key = it->first;
    switch (key) {
      case StatusPanelView::FixedAngleKey: {
        _view->set(StatusPanelView::FixedAngleKey, ray->getFixedAngleDeg());
        break;
      }
      case StatusPanelView::VolumeNumberKey: {
        _view->set(StatusPanelView::VolumeNumberKey, ray->getVolumeNumber());
        break;
      }
      case StatusPanelView::SweepNumberKey: {
        _view->set(StatusPanelView::SweepNumberKey, ray->getSweepNumber());
        break;  
      }
      case StatusPanelView::NSamplesKey: { 
        _view->set(StatusPanelView::NSamplesKey, ray->getNSamples());
        break;
      }
      case StatusPanelView::NGatesKey: {
        _view->set(StatusPanelView::NGatesKey, ray->getNGates());   
        break;   
      }
      case StatusPanelView::GateSpacingKey: {
        _view->set(StatusPanelView::GateSpacingKey, ray->getGateSpacingKm());
        break;
      }
      case StatusPanelView::PulseWidthKey: {
        _view->set(StatusPanelView::PulseWidthKey, ray->getPulseWidthUsec());
        break;
      }
  //case StatusPanelView::PrfModeKey:
  // _view->set(StatusPanelView::
  //case StatusPanelView::_prf) _view->set(StatusPanelView::

      case StatusPanelView::NyquistKey: {
        _view->set(StatusPanelView::NyquistKey, ray->getNyquistMps());
        break;
      }
      case StatusPanelView::MaxRangeKey: {
        double maxRangeData = ray->getStartRangeKm() +
          ray->getNGates() * ray->getGateSpacingKm();
        _view->set(StatusPanelView::MaxRangeKey, maxRangeData);
        break;
      }
      case StatusPanelView::UnambiguousRangeKey: {
        if (fabs(ray->getUnambigRangeKm()) < 100000) {
          _view->set(StatusPanelView::UnambiguousRangeKey, ray->getUnambigRangeKm());
        }
        break;
      }
      case StatusPanelView::PowerHKey: {
        if (ray->getMeasXmitPowerDbmH() > -9990) {
          _view->set(StatusPanelView::PowerHKey, ray->getMeasXmitPowerDbmH());
        }
        break;
      }
      case StatusPanelView::PowerVKey: {
        if (ray->getMeasXmitPowerDbmV() > -9990) {
          _view->set(StatusPanelView::PowerVKey, ray->getMeasXmitPowerDbmV());
        }
        break;
      }
      case StatusPanelView::ScanNameKey: {
        //_view->set(StatusPanelView::ScanNameKey, ray->getScanName().substr(0, 8));
        break;
      }
      case StatusPanelView::SweepModeKey: {
//        _view->set(StatusPanelView::SweepModeKey, 
//          _view->translateSweepMode(ray->getSweepMode());
        break;
      }
      case StatusPanelView::PolarizationModeKey: {
        //_view->setString(StatusPanelView::PolarizationModeKey, 
        //  Radx::polarizationModeToStr(ray->getPolarizationMode()).c_str());
        break;
      }
      // PrfMode?
      
      case StatusPanelView::LatitudeKey:
      case StatusPanelView::LongitudeKey:
      case StatusPanelView::AltitudeInFeetKey:
      case StatusPanelView::AltitudeInKmKey:
      case StatusPanelView::AltitudeRateFtsKey:
      case StatusPanelView::AltitudeRateMsKey:
      case StatusPanelView::SpeedKey:
      case StatusPanelView::HeadingKey:
      case StatusPanelView::TrackKey: {
        _chooseGeoReferenceOrPlatform(ray, key);
        break;
      }
      // deal with this ...
/*
  if (fabs(_radarLat - _platform.getLatitudeDeg()) > 0.0001 ||
      fabs(_radarLon - _platform.getLongitudeDeg()) > 0.0001 ||
      fabs(_radarAltKm - _platform.getAltitudeKm()) > 0.0001) {
    _radarLat = _platform.getLatitudeDeg();
    _radarLon = _platform.getLongitudeDeg();
    _radarAltKm = _platform.getAltitudeKm();
    _sunPosn.setLocation(_radarLat, _radarLon, _radarAltKm * 1000.0);
  }
*/
//    case StatusPanelView::SunElevationKey:
//     _view->set(StatusPanelView::SunElevationKey
//      break;
//    case StatusPanelView::SunAzimuthKey:
//     _view->set(StatusPanelView::SunAzimuthKey
//      break;
      
      default: {
        cerr << "not found" << endl;
        break;
      }
    }
    // if airborne data ...
    if (ray->getSweepMode() == Radx::SWEEP_MODE_ELEVATION_SURVEILLANCE) {
      _updateGeoreferencedData(ray);
    }
  }
}

void StatusPanelController::_updateGeoreferencedData(const RadxRay *ray) {
// need to create and update; because only know if airborne data 
  // once we have a ray ... HERE
  // no need to keep these keys in the hashy, because they are always
  // on. They are hidden be default. 


  const RadxGeoref *georef = ray->getGeoreference();
  if (georef != NULL) {
        string value("");
        if (ray->getGeorefApplied())
          value.append("true");
        else 
          value.append("false");
        //_view->set(StatusPanelView::GeoRefsAppliedKey, value);

        _view->set(StatusPanelView::GeoRefRollKey, georef->getRoll());
        _view->set(StatusPanelView::GeoRefTiltKey, georef->getTilt());
        _view->set(StatusPanelView::GeoRefTrackRelRotationKey, georef->getTrackRelRot()); 
        _view->set(StatusPanelView::GeoRefTrackRelTiltKey, georef->getTrackRelTilt()); 
        _view->set(StatusPanelView::GeoRefTrackRelAzimuthKey, georef->getTrackRelAz()); 
        _view->set(StatusPanelView::GeoRefTrackRelElevationKey, georef->getTrackRelEl());  

  // TODO: these are coupled; show one, show all; depends on 
    // if airborne data ...
        double rollCorr = 0.0;
        double rotCorr = 0.0;
        double tiltCorr = 0.0;
        DataModel *dataModel = DataModel::Instance();
        dataModel->getCfactors(&rollCorr, &rotCorr, &tiltCorr);
        _view->set(StatusPanelView::CfacRotationKey, rotCorr); 
        _view->set(StatusPanelView::CfacRollKey, rollCorr); 
        _view->set(StatusPanelView::CfacTiltKey, tiltCorr); 

      /*

        if (ray->getGeorefApplied()) {
          _georefsApplied->setText("true");       
        } else {
          _georefsApplied->setText("false");          
        }

        _setText(text, "%.3f", georef->getRotation());  
        _geoRefRotationVal->setText(text); 
        _setText(text, "%.3f", georef->getRoll());  
        _geoRefRollVal->setText(text); 
        _setText(text, "%.3f", georef->getTilt());  
        _geoRefTiltVal->setText(text);

        _setText(text, "%.3f", georef->getTrackRelRot());  
        _geoRefTrackRelRotationVal->setText(text); 
        _setText(text, "%.3f", georef->getTrackRelTilt());  
        _geoRefTrackRelTiltVal->setText(text);
        _setText(text, "%.3f", georef->getTrackRelAz());  
        _geoRefTrackRelAzVal->setText(text); 
        _setText(text, "%.3f", georef->getTrackRelEl());  
        _geoRefTrackRelElVal->setText(text); 

        double rollCorr = 0.0;
        double rotCorr = 0.0;
        double tiltCorr = 0.0;
        DataModel *dataModel = DataModel::Instance();
        dataModel->getCfactors(&rollCorr, &rotCorr, &tiltCorr);
        _setText(text, "%.3f", rollCorr);
        _cfacRollVal->setText(text);
        _setText(text, "%.3f", rotCorr);
        _cfacRotationVal->setText(text);   
        _setText(text, "%.3f", tiltCorr);    
        _cfacTiltVal->setText(text);
*/
      }

      //_view->showCfacs();
}

/*
void StatusPanelController::_showCfactors(int key) {
// TODO: these are coupled; show one, show all; depends on 
  // if airborne data ...
//   {

    case StatusPanelView::CfacRotationKey:
        _view->set(StatusPanelView::CfacRotationKey
      break;
    case StatusPanelView::CfacRollKey:
      if (georef != NULL)
        _view->set(StatusPanelView::CfacRollKey
      break;
    case StatusPanelView::CfacTiltKey:
      if (georef != NULL)
        _view->set(StatusPanelView::CfacTiltKey
      break;     
}
*/

double StatusPanelController::_calculateSpeed(double ewVel, double nsVel) {
      double speed = sqrt(ewVel * ewVel + nsVel * nsVel);
      return speed;
}

void StatusPanelController::_getInfoFromGeoreference(const RadxGeoref *georef,
   RadxTime rayTime, int key) {
    switch (key) {
      case StatusPanelView::LatitudeKey: {
        _view->set(StatusPanelView::LatitudeKey, georef->getLatitude());
        break; 
      }
      case StatusPanelView::LongitudeKey:
        _view->set(StatusPanelView::LongitudeKey, georef->getLongitude());
        break; 
      case StatusPanelView::AltitudeInFeetKey: {
        double radarAltFeet = georef->getAltitudeKmMsl() / 0.3048;
        _view->set(StatusPanelView::AltitudeInFeetKey, radarAltFeet);
        break; 
      }
      case StatusPanelView::AltitudeInKmKey:
        _view->set(StatusPanelView::AltitudeInKmKey, georef->getAltitudeKmMsl());
        break;

      /* 

      case StatusPanelView::AltitudeRateFtsKey:
        _view->set(StatusPanelView::AltitudeRateFtsKey, georef->getLatitude());
        break;
      case StatusPanelView::AltitudeRateMsKey:
        _view->set(StatusPanelView::AltitudeRateMsKey, georef->getLatitude());
        break;
        */
      case StatusPanelView::SpeedKey: {
        double value = _calculateSpeed(georef->getEwVelocity(),
          georef->getNsVelocity());
        _view->set(StatusPanelView::SpeedKey, value);
        break;
      }
      case StatusPanelView::HeadingKey: {
        double heading = georef->getHeading();
        if (heading >= 0 && heading <= 360.0) {
          _view->set(StatusPanelView::HeadingKey, heading);
        }
        break;
      }
      case StatusPanelView::TrackKey: {
        double track = georef->getTrack();
        if (track >= 0 && track <= 360.0) {
          _view->set(StatusPanelView::TrackKey, track);
        }        
        break;
      }
      default: {
        cerr << "something awful happened" << endl;
      }
    }

    /*


    // compute altitude rate every 2 secs
    
    if (_prevAltKm > -9990) {
      double deltaTime = ray->getRadxTime() - _prevAltTime;
      if (deltaTime > 2.0) {
        double altKm = ray->getGeoreference()->getAltitudeKmMsl();
        double deltaAltKm = altKm - _prevAltKm;
        _altRateMps = (deltaAltKm / deltaTime) * 1000.0;
        _prevAltKm = ray->getGeoreference()->getAltitudeKmMsl();
        _prevAltTime = ray->getRadxTime();
      }
    } else {
      _prevAltKm = ray->getGeoreference()->getAltitudeKmMsl();
      _prevAltTime = ray->getRadxTime();
    }
    
    if (_altitudeInFeet) {
      _setText(text, "%.1f", _altRateMps / 0.3048);
    } else {
      _setText(text, "%.1f", _altRateMps);
    }
    if (_altRateVal) {
      _altRateVal->setText(text);
    }
*/
}

void StatusPanelController::_getInforFromPlatform(const RadxRay *ray, int key) {

  DataModel *dataModel = DataModel::Instance();  
  const RadxPlatform platform = dataModel->getPlatform();
  switch (key) {
    case StatusPanelView::LatitudeKey:
      _view->set(StatusPanelView::LatitudeKey, platform.getLongitudeDeg());
      break; 
    case StatusPanelView::LongitudeKey:
      _view->set(StatusPanelView::LongitudeKey, _platform.getLongitudeDeg());
      break; 
    case StatusPanelView::AltitudeInFeetKey: {
      double radarAltFeet = _platform.getAltitudeKm()  / 0.3048;
      _view->set(StatusPanelView::AltitudeInFeetKey, radarAltFeet);
      break; 
    }
    case StatusPanelView::AltitudeInKmKey:
      _view->set(StatusPanelView::AltitudeInKmKey, _platform.getAltitudeKm() );
      break;
    default:
      cerr << "something really awful happened" << endl;
    }
}

void StatusPanelController::_chooseGeoReferenceOrPlatform(const RadxRay *ray, int key) {
  const RadxGeoref *georef = ray->getGeoreference();
  if (georef != NULL) {
    _getInfoFromGeoreference(georef, ray->getRadxTime(), key);     
  } else {
    _getInforFromPlatform(ray, key);
  }
}

void StatusPanelController::setFontSize(int fontSize) {
  _view->setFontSize(fontSize);
}

/*
string StatusPanelController::interpretPrf(Radx::  rayPrtMode, double rayPrtSec, double rayPrtRatio) {
  string text;

    if (_view->_prfVal) {
    if (ray->getPrtMode() == Radx::PRT_MODE_FIXED) {
      if (ray->getPrtSec() <= 0) {
        _setText(text, "%d", -9999);
      } else {
        _setText(text, "%d", (int) ((1.0 / ray->getPrtSec()) * 10.0 + 0.5) / 10);
      }
    } else {
      double prtSec = rayPrtSec;
      if (prtSec <= 0) {
        _setText(text, "%d", -9999);
      } else {
        int iprt = (int) ((1.0 / rayPrtSec) * 10.0 + 0.5) / 10;
        double prtRatio = rayPrtRatio;
        if (prtRatio > 0.6 && prtRatio < 0.7) {
          _setText(text, "%d(2/3)", iprt);
        } else if (prtRatio < 0.775) {
          _setText(text, "%d(3/4)", iprt);
        } else if (prtRatio < 0.825) {
          _setText(text, "%d(4/5)", iprt);
        } else {
          _setText(text, "%d", iprt);
        }
      }
    }
    _prfVal->setText(text);
  }
  return text;
}
*/

string StatusPanelController::interpretSweepMode(Radx::SweepMode_t sweepMode) {

    switch (sweepMode) {
      case Radx::SWEEP_MODE_SECTOR: {
        return "sector"; break;
      }
      case Radx::SWEEP_MODE_COPLANE: {
        return "coplane"; break;
      }
      case Radx::SWEEP_MODE_RHI: {
        return "RHI"; break;
      }
      case Radx::SWEEP_MODE_VERTICAL_POINTING: {
        return "vert"; break;
      }
      case Radx::SWEEP_MODE_IDLE: {
        return "idle"; break;
      }
      case Radx::SWEEP_MODE_AZIMUTH_SURVEILLANCE:
      case Radx::SWEEP_MODE_ELEVATION_SURVEILLANCE: {
        return "SUR"; break;
      }
      case Radx::SWEEP_MODE_SUNSCAN: {
        return "sunscan"; break;
      }
      case Radx::SWEEP_MODE_SUNSCAN_RHI: {
        return "sun_rhi"; break;
      }
      case Radx::SWEEP_MODE_POINTING: {
        return "point"; break;
      }
      case Radx::SWEEP_MODE_CALIBRATION: {
        return "cal"; break;
      }
      default: {
        return "unknown";
      }
    }
}

void StatusPanelController::newDataFile() {
  //clear();
}
/*
//////////////////////////////////////////////////

  // create status panel

  _createStatusPanel();

void StatusPanel::selectedSweepChanged(int sweepNumber) {
  LOG(DEBUG) << "enter"; 
  //string fieldName = newFieldName.toStdString();
  //_displayFieldController->setSelectedField(fieldName);
  if (_sweepController->getSelectedNumber() != sweepNumber) {
    _sweepController->setSelectedNumber(sweepNumber);
    _readDataFile();
    // signal polar display to update; which causes rayLocations to update
    selectedFieldChanged(_displayFieldController->getSelectedFieldName());
    emit newSweepData(sweepNumber);
    //processEvents();
    //_setupRayLocation();  // this is done by _getArchiveData
    //_plotArchiveData();
    //refreshBoundaries();
  } else {
    if (sheetView != NULL) {
      spreadSheetControl->displaySweepData(sweepNumber);
    }
  }
  LOG(DEBUG) << "exit";
}

*/



