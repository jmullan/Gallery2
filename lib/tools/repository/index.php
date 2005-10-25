<?php
/**
 * @package RepositoryTools
 */
include('../../support/security.inc');
include('../../../bootstrap.inc');
require_once('../../../init.inc');

function RepositoryToolsMain() {
    $ret = GalleryInitFirstPass();
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    $ret = GalleryInitSecondPass();
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    global $gallery;

    GalleryCoreApi::relativeRequireOnce(
	'lib/tools/repository/classes/RepositoryControllerAndView.class');

    /* Set repository configuration data. */
    $gallery->setConfig('repository.path',
	'/home/titanium/eclipse-workspace/Gallery2/lib/tools/repository/data/');
    $gallery->setConfig('repository.templates',
	'lib/tools/repository/templates/');

    /* Configure our url Generator for repository mode. */
    $urlGenerator = new GalleryUrlGenerator();
    $urlGenerator->init('lib/tools/repository/index.php');
    $gallery->setUrlGenerator($urlGenerator);

    /* Load controller. */
    $controllerName = GalleryUtilities::getRequestVariables('controller');
    $methodName = GalleryUtilities::getRequestVariables('action');
    $controllerPath = sprintf('%s/%s.inc', dirname(__FILE__), $controllerName);

    $platform = $gallery->getPlatform();
    if (!$platform->file_exists($controllerPath)) {
	/* Set default controller. */
	$controllerName = 'MainPage';
	$controllerPath = sprintf('%s/%s.inc', dirname(__FILE__), $controllerName);
	$methodName = 'showAvailableActions';
    }

    $controllerClassName = $controllerName . 'ControllerAndView';
    require_once($controllerPath);
    $controller = new $controllerClassName();
    $controller->init();

    /* Call a controller method. */
    if (!method_exists($controller, $methodName)) {
	return GalleryStatus::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__,
				    "Method [$methodName] does not exist in $controllerClassName");
    }

    $ret = $controller->$methodName();
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    return GalleryStatus::success();
}

$ret = RepositoryToolsMain();
if ($ret->isError()) {
    $ret = $ret->wrap(__FILE__, __LINE__);
    print $ret->getAsHtml();
    print $gallery->getDebugBuffer();
    return;
}

list ($ret, $isSiteAdmin) = GalleryCoreApi::isUserInSiteAdminGroup();
if ($ret->isError()) {
    $ret = $ret->wrap(__FILE__, __LINE__);
    print $ret->getAsHtml();
    return;
}
?>