/**
 *  JavaScript utility library for the Simulink Web View
 *
 *  Copyright 1997-2007 The MathWorks, Inc.
 */

//  Declare this one time to avoid reevaluating
USES_IE = false;
//    Alias browser specific calls...
if(navigator.userAgent.toLowerCase().indexOf("msie") != -1)
{
    USES_IE = true;
    addEventListener = addEventListenerIE;
    getEvent = getEventIE;
    getMouseX = getMouseXIE;
    getMouseY = getMouseYIE;
    hasSVGSupport = hasSVGSupportIE;
}
else
{
    USES_IE = false;
    addEventListener = addEventListenerMoz;
    getEvent = getEventMoz;
    getMouseX = getMouseXMoz;
    getMouseY = getMouseYMoz;
    hasSVGSupport = hasSVGSupportMoz;
}

/**
 *  Object to help load svg images
 */
function SvgLoader(filename) 
{
    this.filename = filename;
}

/**
 *  Load svg by writing out EMBED or Object tag for the SVG file
 */
SvgLoader.prototype.execute = function() 
{
    if (hasAdobeSVGPlugin()) {
        // IE with ASV does capture wheel mouse and arrow keys!  We will add
        // listeners here to capture these events before they make it to ASV.
        // For other browser, we add listeners in slwebview.js.
        document.onmousewheel = wheel;
    
        document.write('<embed height="100%" width="100%" '
            + 'src="' + this.filename + '" type="image/svg+xml" '
            + 'pluginspage="http://www.adobe.com/svg/viewer/install/">'
            + '</embed>');
    } else if (hasSVGSupport()) {
        document.write('<object height="100%" width="100%" '
            + 'data="' + this.filename + '" type="image/svg+xml">'
            + '</object>');
    } else {
        document.write(gMsgMap["NoSVGSupport"]);
    }
}

/**
 * Checks if the Adobe SVG Plugin is installed, via a VBScript
 */
function hasAdobeSVGPlugin()
{
    var userAgent = navigator.userAgent.toLowerCase();
    var isWin = (userAgent.indexOf("win") != -1);

    if (isWin) {
        document.write('<SCRIPT LANGUAGE="VBScript">\n' 
                        + 'on error resume next \n' 
                        + 'isASVinstalled = IsObject(CreateObject("Adobe.SVGCtl"))' 
                        + '</SCRIPT>\n');
        return window.isASVinstalled;
    }
    return false;
}

/***********************/
/**    IE Specific calls  **/    
function addEventListenerIE(domObject, eventName, callback)
{
    eval("domObject.on" + eventName.toLowerCase() + " = callback;");
}
function getEventIE(evt)
{
    return window.event;
}
function getMouseXIE(evt)
{
    return getEvent(evt).x;
}
function getMouseYIE(evt)
{
    return getEvent(evt).y;
}
/**
 *  Basic SVG support detection.  Will only fail if IE 6&7 with no ASV plugin.
 */
function hasSVGSupportIE()
{
    var userAgent = navigator.userAgent.toLowerCase();

    var reg = /msie (\d+.\d+)/;
    var regResult = reg.exec(userAgent);

    if (regResult.length > 1) {
        var ieVer = parseFloat(regResult[1]);
        //  If this is IE 6 or 7, look for the Adobe SVG plugin
        if(ieVer >= 6 && ieVer <= 7)
            return hasAdobeSVGPlugin();
    }

    return true;
}

/*************************/
/**  Non-IE specific calls  **/
function addEventListenerMoz(domObject, eventName, callback)
{
    domObject.addEventListener(eventName, callback, false);
}
function getEventMoz(evt)
{
    return evt;
}
function getMouseXMoz(evt)
{
    return getEvent(evt).clientX;
}
function getMouseYMoz(evt)
{
    return getEvent(evt).clientY;
}
function hasSVGSupportMoz()
{
    return true;
}
/*************************/

g__TOOLTIP = null;
function showToolTip(content, left, top)
{
    if(g__TOOLTIP == null)
        g__TOOLTIP = createNewToolTip();
        
    g__TOOLTIP.firstChild.innerHTML = content;
    g__TOOLTIP.style.left = left;
    g__TOOLTIP.style.top = top;
    g__TOOLTIP.style.display = "";
}
function createNewToolTip()
{
    var tooltip = document.createElement("div");
    tooltip.className = "tooltipContainer";
    tooltip.style.display = "none";
    
    var subDiv = document.createElement("div");
    tooltip.appendChild(subDiv);
    
    subDiv.className = "tooltipContent";

    document.body.appendChild(tooltip);
    
    return tooltip;
}
function hideToolTip()
{
    if(g__TOOLTIP != null)
    {
        g__TOOLTIP.style.display = "none";
    }
}
function getOffsetLeft(domObj)
{
    if(domObj == null || domObj == undefined)
    {
        return 0;
    }
    
    return domObj.offsetLeft + getOffsetLeft(domObj.offsetParent);
}
function getOffsetTop(domObj)
{
    if(domObj == null || domObj == undefined)
    {
        return 0;
    }
    
    return domObj.offsetTop + getOffsetTop(domObj.offsetParent);
}
