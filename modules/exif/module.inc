<?php
/*
 * $RCSfile$
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2003 Bharat Mediratta
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */
/**
 * @package Exif
 * @version $Revision$ $Date$
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * Simple EXIF setting
 */
define("EXIF_SIMPLE", 1);

/**
 * Advanced EXIF setting
 */
define("EXIF_ADVANCED", 2);

/**
 * Hidden EXIF setting
 */
define("EXIF_HIDDEN", 3);

/**
 * Exif Module
 *
 * This module provides support for adding exifs to items
 *
 * @package Exif
 */
class ExifModule extends GalleryModule {

    function ExifModule() {
	global $gallery;
	
	$this->setId('exif');
	$this->setName('Exif Parser');
	$this->setDescription($gallery->i18n('Extract EXIF data from JPEG photos'));
	$this->setVersion('1.0');
    }

    /**
     * @see GalleryModule::init()
     */
    function init() {
	global $gallery;

	$ret = parent::init();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	require_once(dirname(__FILE__) . '/lib/exifer/exif.inc');
	
	return GalleryStatus::success();
    }

    /**
     * @see GalleryModule::install()
     */
    function install() {
	global $gallery;
	
	list ($ret, $version) = $this->getModuleParameter('version');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	if ($version != $this->getVersion()) {

	    if (empty($version)) {
		/*
		 * This is an initial install. Make sure that we have some
		 * reasonable defaults.
		 */
		foreach (array() as $key => $value) {

		    $ret = $this->setModuleParameter($key, $value);
		    if ($ret->isError()) {
			return $ret->wrap(__FILE__, __LINE__);
		    }
		}
	    }

	    $ret = $this->setModuleParameter('version', $this->getVersion());
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	}
	
	return GalleryStatus::success();
    }
	
    /**
     * @see GalleryModule::loadItemDetails()
     */
    function loadItemDetails(&$template, $item) {
	global $gallery;

	/* We only work on data items */
	if (!GalleryUtilities::isA($item, 'GalleryDataItem')) {
	    return array(GalleryStatus::success(), '');
	}

	/* And those data items have to be JPEGs */
	if ($item->getMimeType() != 'image/jpeg') {
	    return array(GalleryStatus::success(), '');
	}
	    
	/* Feed the file to exifer */
	list($ret, $path) = $item->fetchPath();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$exifData = read_exif_data_raw($path, false);
	$gallery->debug(str_replace("\0", '', print_r($exifData, 1)));

	$ExifItemDetails = array();
	$ExifItemDetails['exifData'] = $exifData;
	$template->setVariable('ExifItemDetails', $ExifItemDetails);

	return array(GalleryStatus::success(), 'modules/exif/templates/ExifItemDetails.tpl');
    }
    
    /**
     * @see GalleryModule::getSiteAdminViews()
     */
    function getSiteAdminViews() {
	global $gallery;

	return array(GalleryStatus::success(),
		     array(array('name' => $this->translate('Exif Parser'),
				 'view' => 'exif:AdminExif')));
    }

    /**
     * @see GalleryModule::getConfigurationView()
     */
    function getConfigurationView() {
	global $gallery;
	return array(GalleryStatus::success(), 'exif:AdminExif');
    }

    function getExifKeys() {
	static $exifKeys;
	if (empty($exifKeys)) {
	    array('general' =>
		  array('IFD0.ACDComment' => EXIF_ADVANCED,
			'IFD0.ImageType' => EXIF_ADVANCED,
			'IFD0.PhotometricInterpret' => EXIF_ADVANCED,
			'IFD0.ImageDescription' => EXIF_ADVANCED,
			'IFD0.Make' => EXIF_SIMPLE,
			'IFD0.Model' => EXIF_SIMPLE,
			'IFD0.Orientation' => EXIF_ADVANCED,
			'IFD0.SamplePerPixel' => EXIF_ADVANCED,
			// 'IFD0.xResolution', 'IFD0.yResolution', 'IFD0.ResolutionUnit',
			'IFD0.Resolution*' => EXIF_ADVANCED, 
			'IFD0.PlanarConfig' => EXIF_ADVANCED,
			'IFD0.Software' => EXIF_ADVANCED,
			'IFD0.DateTime' => EXIF_SIMPLE,
			'IFD0.Artist' => EXIF_ADVANCED,
			'IFD0.WhitePoint' => EXIF_ADVANCED,
			'IFD0.PrimaryChromaticities' => EXIF_ADVANCED,
			'IFD0.YCbCrCoefficients' => EXIF_ADVANCED,
			'IFD0.YCbCrPositioning' => EXIF_ADVANCED,
			'IFD0.ReferenceBlackWhite' => EXIF_ADVANCED,
			'IFD0.Copyright' => EXIF_ADVANCED,
			'IFD0.PhotoshopSettings' => EXIF_ADVANCED,
			'IFD0.GPSInfoOffset' => EXIF_ADVANCED,
			'IFD0.UserCommentOld' => EXIF_ADVANCED,
			'IFD0.ExifOffset' => EXIF_ADVANCED,
			'SubIFD.ExposureTime' => EXIF_SIMPLE,
			'SubIFD.FNumber' => EXIF_SIMPLE,
			'SubIFD.ExposureProgram' => EXIF_SIMPLE,
			'SubIFD.SpectralSensitivity' => EXIF_ADVANCED,
			'SubIFD.ISOSpeedRatings' => EXIF_SIMPLE,
			'SubIFD.ExifVersion' => EXIF_ADVANCED,
			'SubIFD.DateTimeOriginal' => EXIF_ADVANCED,
			'SubIFD.DateTimeDigitized' => EXIF_ADVANCED,
			'SubIFD.ComponentsConfiguration' => EXIF_ADVANCED,
			'SubIFD.CompressedBitsPerPixel' => EXIF_ADVANCED,
			'SubIFD.ShutterSpeedValue' => EXIF_SIMPLE,
			'SubIFD.ApertureValue' => EXIF_SIMPLE,
			'SubIFD.BrightnessValue' => EXIF_ADVANCED,
			'SubIFD.ExposureBiasValue' => EXIF_SIMPLE,
			'SubIFD.MaxApertureValue' => EXIF_ADVANCED,
			'SubIFD.SubjectDistance' => EXIF_ADVANCED,
			'SubIFD.MeteringMode' => EXIF_SIMPLE,
			'SubIFD.LightSource' => EXIF_ADVANCED,
			'SubIFD.Flash' => EXIF_SIMPLE,
			'SubIFD.FocalLength' => EXIF_SIMPLE,
			'SubIFD.ImageHistory' => EXIF_ADVANCED,
			'SubIFD.MakerNote' => EXIF_ADVANCED,
			'SubIFD.UserComment' => EXIF_ADVANCED,
			'SubIFD.SubsecTime' => EXIF_ADVANCED,
			'SubIFD.SubsecTimeOriginal' => EXIF_ADVANCED,
			'SubIFD.SubsecTimeDigitized' => EXIF_ADVANCED,
			'SubIFD.FlashPixVersion' => EXIF_ADVANCED,
			'SubIFD.ColorSpace' => EXIF_SIMPLE,
			'SubIFD.ExifImageWidth' => EXIF_ADVANCED,
			'SubIFD.ExifImageHeight' => EXIF_ADVANCED,
			'SubIFD.RelatedSoundFile' => EXIF_ADVANCED,
			'SubIFD.ExifInteroperabilityOffset' => EXIF_ADVANCED,
			'SubIFD.SpacialFreqResponse' => EXIF_ADVANCED,
			'SubIFD.FlashEnergy' => EXIF_ADVANCED,
			'SubIFD.FocalPlaneXResolution' => EXIF_ADVANCED,
			'SubIFD.FocalPlaneYResolution' => EXIF_ADVANCED,
			'SubIFD.FocalPlaneResolutionUnit' => EXIF_ADVANCED,
			'SubIFD.SubjectLocation' => EXIF_ADVANCED,
			'SubIFD.ExposureIndex' => EXIF_ADVANCED,
			'SubIFD.SensingMethod' => EXIF_ADVANCED,
			'SubIFD.FileSource' => EXIF_ADVANCED,
			'SubIFD.SceneType' => EXIF_ADVANCED,
			'SubIFD.CFAPattern' => EXIF_ADVANCED,
			'SubIFD.CustomerRender' => EXIF_ADVANCED,
			'SubIFD.ExposureMode' => EXIF_ADVANCED,
			'SubIFD.WhiteBalance' => EXIF_ADVANCED,
			'SubIFD.DigitalZoomRatio' => EXIF_ADVANCED,
			'SubIFD.SceneCaptureMode' => EXIF_ADVANCED,
			'SubIFD.GainControl' => EXIF_ADVANCED,
			'SubIFD.Contrast' => EXIF_ADVANCED,
			'SubIFD.Saturation' => EXIF_ADVANCED,
			'SubIFD.Sharpness' => EXIF_ADVANCED,
			'InteroperabilityIFD.InteroperabilityIndex' => EXIF_ADVANCED,
			'InteroperabilityIFD.InteroperabilityVersion' => EXIF_ADVANCED,
			'InteroperabilityIFD.RelatedImageFileFormat' => EXIF_ADVANCED,
			'InteroperabilityIFD.RelatedImageWidth' => EXIF_ADVANCED,
			'InteroperabilityIFD.RelatedImageLength' => EXIF_ADVANCED,
			'IFD1.ImageWidth' => EXIF_ADVANCED,
			'IFD1.ImageLength' => EXIF_ADVANCED,
			'IFD1.BitsPerSample' => EXIF_ADVANCED,
			'IFD1.Compression' => EXIF_ADVANCED,
			'IFD1.PhotometricInterpretation' => EXIF_ADVANCED,
			'IFD1.ThumbnailDescription' => EXIF_ADVANCED,
			'IFD1.ThumbnailMake' => EXIF_ADVANCED,
			'IFD1.ThumbnailModel' => EXIF_ADVANCED,
			'IFD1.StripOffsets' => EXIF_ADVANCED,
			'IFD1.ThumbnailOrientation' => EXIF_ADVANCED,
			'IFD1.SamplesPerPixel' => EXIF_ADVANCED,
			'IFD1.RowsPerStrip' => EXIF_ADVANCED,
			'IFD1.StripByteCounts' => EXIF_ADVANCED,
			'IFD1.ThumbnailXResolution' => EXIF_ADVANCED,
			'IFD1.ThumbnailYResolution' => EXIF_ADVANCED,
			'IFD1.PlanarConfiguration' => EXIF_ADVANCED,
			'IFD1.ThumbnailResolutionUnit' => EXIF_ADVANCED,
			'IFD1.JpegIFOffset' => EXIF_ADVANCED,
			'IFD1.JpegIFByteCount' => EXIF_ADVANCED,
			'IFD1.YCbCrSubSampling' => EXIF_ADVANCED,
			'IFD1.SubfileType' => EXIF_ADVANCED,
			'IFD1.TransferFunction' => EXIF_ADVANCED,
			'IFD1.Predictor' => EXIF_ADVANCED,
			'IFD1.TileWidth' => EXIF_ADVANCED,
			'IFD1.TileLength' => EXIF_ADVANCED,
			'IFD1.TileOffsets' => EXIF_ADVANCED,
			'IFD1.TileByteCounts' => EXIF_ADVANCED,
			'IFD1.SubIFDs' => EXIF_ADVANCED,
			'IFD1.JPEGTables' => EXIF_ADVANCED,
			'IFD1.CFARepeatPatternDim' => EXIF_ADVANCED,
			'IFD1.CFAPattern' => EXIF_ADVANCED,
			'IFD1.BatteryLevel' => EXIF_ADVANCED,
			'IFD1.IPTC/NAA' => EXIF_ADVANCED,
			'IFD1.InterColorProfile' => EXIF_ADVANCED,
			'IFD1.OECF' => EXIF_ADVANCED,
			'IFD1.Interlace' => EXIF_ADVANCED,
			'IFD1.TimeZoneOffset' => EXIF_ADVANCED,
			'IFD1.SelfTimerMode' => EXIF_ADVANCED,
			'IFD1.FlashEnergy' => EXIF_ADVANCED,
			'IFD1.SpatialFrequencyResponse' => EXIF_ADVANCED,
			'IFD1.Noise' => EXIF_ADVANCED,
			'IFD1.ImageNumber' => EXIF_ADVANCED,
			'IFD1.SecurityClassification' => EXIF_ADVANCED,
			'IFD1.SubjectLocation' => EXIF_ADVANCED,
			'IFD1.ExposureIndex' => EXIF_ADVANCED,
			'IFD1.TIFF/EPStandardID' => EXIF_ADVANCED,
			'IFD1.FlashEnergy' => EXIF_ADVANCED,
			),
		  'makers' =>
		  array('Canon' => array('Settings 1' => EXIF_ADVANCED,
					 'Settings 4' => EXIF_ADVANCED,
					 'ImageType' => EXIF_ADVANCED,
					 'FirmwareVersion' => EXIF_ADVANCED,
					 'ImageNumber' => EXIF_ADVANCED,
					 'OwnerName' => EXIF_ADVANCED,
					 'CameraSerialNumber' => EXIF_ADVANCED,
					 'CustomFunctions' => EXIF_ADVANCED),
			'FujiFilm' => array('Version' => EXIF_ADVANCED,
					    'Quality' => EXIF_ADVANCED,
					    'Sharpness' => EXIF_ADVANCED,
					    'WhiteBalance' => EXIF_ADVANCED,
					    'Color' => EXIF_ADVANCED,
					    'Tone' => EXIF_ADVANCED,
					    'FlashMode' => EXIF_ADVANCED,
					    'FlashStrength' => EXIF_ADVANCED,
					    'Macro' => EXIF_ADVANCED,
					    'FocusMode' => EXIF_ADVANCED,
					    'SlowSync' => EXIF_ADVANCED,
					    'PictureMode' => EXIF_ADVANCED,
					    'ContinuousTakingBracket' => EXIF_ADVANCED,
					    'BlurWarning' => EXIF_ADVANCED,
					    'FocusWarning' => EXIF_ADVANCED,
					    'AEWarning' => EXIF_ADVANCED),
			'GPS' => array('Maker.Version' => EXIF_ADVANCED,
				       'Latitude Reference' => EXIF_ADVANCED,
				       'Latitude' => EXIF_ADVANCED,
				       'Longitude Reference' => EXIF_ADVANCED,
				       'Longitude' => EXIF_ADVANCED,
				       'Altitude Reference' => EXIF_ADVANCED,
				       'Altitude' => EXIF_ADVANCED,
				       'Time' => EXIF_ADVANCED,
				       'Satellite' => EXIF_ADVANCED,
				       'ReceiveStatus' => EXIF_ADVANCED,
				       'MeasurementMode' => EXIF_ADVANCED,
				       'MeasurementPrecision' => EXIF_ADVANCED,
				       'SpeedUnit' => EXIF_ADVANCED,
				       'ReceiverSpeed' => EXIF_ADVANCED,
				       'MovementDirectionRef' => EXIF_ADVANCED,
				       'MovementDirection' => EXIF_ADVANCED,
				       'ImageDirectionRef' => EXIF_ADVANCED,
				       'ImageDirection' => EXIF_ADVANCED,
				       'GeodeticSurveyData' => EXIF_ADVANCED,
				       'DestLatitudeRef' => EXIF_ADVANCED,
				       'DestinationLatitude' => EXIF_ADVANCED,
				       'DestLongitudeRef' => EXIF_ADVANCED,
				       'DestinationLongitude' => EXIF_ADVANCED,
				       'DestBearingRef' => EXIF_ADVANCED,
				       'DestinationBearing' => EXIF_ADVANCED,
				       'DestDistanceRef' => EXIF_ADVANCED,
				       'DestinationDistance' => EXIF_ADVANCED,
				       'ProcessingMethod' => EXIF_ADVANCED,
				       'AreaInformation' => EXIF_ADVANCED,
				       'Datestamp' => EXIF_ADVANCED,
				       'DifferentialCorrection' => EXIF_ADVANCED),
			'Nikon' => array('Quality' => EXIF_ADVANCED,
					 'ColorMode' => EXIF_ADVANCED,
					 'ImageAdjustment' => EXIF_ADVANCED,
					 'CCDSensitivity' => EXIF_ADVANCED,
					 'WhiteBalance' => EXIF_ADVANCED,
					 'Focus' => EXIF_ADVANCED,
					 'DigitalZoom' => EXIF_ADVANCED,
					 'Converter' => EXIF_ADVANCED,
					 'ISOSetting' => EXIF_ADVANCED,
					 'ColorMode' => EXIF_ADVANCED,
					 'Quality' => EXIF_ADVANCED,
					 'Whitebalance' => EXIF_ADVANCED,
					 'ImageSharpening' => EXIF_ADVANCED,
					 'FocusMode' => EXIF_ADVANCED,
					 'FlashSetting' => EXIF_ADVANCED,
					 'ISOSelection' => EXIF_ADVANCED,
					 'ImageAdjustment' => EXIF_ADVANCED,
					 'Adapter' => EXIF_ADVANCED,
					 'ManualFocusDistance' => EXIF_ADVANCED,
					 'DigitalZoom' => EXIF_ADVANCED,
					 'AFFocusPosition' => EXIF_ADVANCED,
					 'Saturation' => EXIF_ADVANCED,
					 'NoiseReduction' => EXIF_ADVANCED,
					 'DataDump' => EXIF_ADVANCED),
			'Olympus' => array('SpecialMode' => EXIF_ADVANCED,
					   'JpegQual' => EXIF_ADVANCED,
					   'Macro' => EXIF_ADVANCED,
					   'DigiZoom' => EXIF_ADVANCED,
					   'SoftwareRelease' => EXIF_ADVANCED,
					   'PictInfo' => EXIF_ADVANCED,
					   'CameraID' => EXIF_ADVANCED,
					   'DataDump' => EXIF_ADVANCED),
			'Sanyo' => array('SpecialMode' => EXIF_ADVANCED,
					 'Quality' => EXIF_ADVANCED,
					 'Macro' => EXIF_ADVANCED,
					 'DigiZoom' => EXIF_ADVANCED,
					 'DataDump' => EXIF_ADVANCED),
			)
		  );
	}
      }    
}
?>