/**
 *  JavaScript library for the Simulink Web View
 *
 *  Copyright 1997-2007 The MathWorks, Inc.
 */

/*============================================================================
 * Initialization and Setup
 *============================================================================*/

var gSVGNS = "http://www.w3.org/2000/svg";
var gXLINKNS = "http://www.w3.org/1999/xlink";

/**
 *  Initialization code.  Called by the SVG file.
 */
function initialize(evt)
{
    var svgState = getSvgState(gHomeSys);

    svgState.homeSys = gHomeSys;
    svgState.svgWindow = window;

    svgState.svgDoc = window.svgDocument;
    if (!svgState.svgDoc) { svgState.svgDoc = document; }

    svgState.canvasGroup = svgState.svgDoc.getElementById('group.canvas');
    svgState.thumbnailGroup = svgState.svgDoc.getElementById('thumbnail.canvas');
    // canvasGroup is null when user load the incremental svg files
    if (!svgState.canvasGroup) { svgState.canvasGroup = svgState.svgDoc; }

    svgState.svgDoc.rootElement.addEventListener('keydown', keyDown, false);
    svgState.svgDoc.rootElement.addEventListener('keyup', keyUp, false);
    svgState.svgDoc.rootElement.addEventListener('DOMMouseScroll', wheel, false); //firefox
    svgState.svgDoc.rootElement.addEventListener('mousewheel', wheel, false); //opera

    customizeContextMenu(evt); //ASV only

    // change to home directory
    changeSysByName(svgState.homeSys, false); // do not add to history

    //rootElement.addEventListener('mouseup', zoomBoxMouseUp, false);
    //rootElement.addEventListener('mousedown', zoomBoxMouseDown, false);
}

/**
 *  Get the svg state object from the top workspace so we can access it from
 *  different context.  Note:  ASV can not access parent/window information.
 */
function getSvgState(id)
{
    if (!id) {
        id = gHomeSys;
    }
    if (!top._slwebview) {
        top._slwebview = new Array();
    }
    if (!top._slwebview[id]) {
        top._slwebview[id] = new svgStateObj();
        top._slwebview[id].homeSys = id;
    }
    return top._slwebview[id];
}

/**
 *  Object to maintain svg state information.
 */
function svgStateObj()
{
    this.svgDoc = false;                // SVG root document node
    this.svgWindow = false;             // SVG window object.  In ASV, this is the plugin object
    this.currSys = "";                  // Current system
    this.homeSys = "";                  // Home system
    this.prevSys = new Array();         // Previous system
    this.currSysCanvas = false;         // Current system canvas

    this.canvasGroup = null;            // place to add layers
    this.thumbnailGroup = null;         // place to add thumbnails
    this.isShowingAllCanvas = false;    // Showing all canvases
    this.showPropertyTables = true;     // To Show property table?

    this.navHomeBtn = false;            // Nav home system button node
    this.prevSysBtn = false;            // Nav previous system button node

    this.lang = "en";
    this.titleTextNodeEn = false;       // English title text node
    this.titleTextNodeJa = false;       // Japanese title test node

    this.dragMode = false;              // Dragging in mouse pan

    this.zoomBox = false;               // rubber band zoom

    this.tree = null;                   // Tree object

    this.spaceTimeoutId = false;            // Timeout id for delaying mouse scrim
    this.spaceMousePanScrimAdded = false;   // Mouse pan added
}

/**
 *  Get the key pressed.  Also maps number pad to regular keyboard keys.
 */
function getKeyChar(evt)
{
    var keyCode;
    try {
        keyCode = evt.keyCode; //ie
    } catch (e) {
        try {
            keyCode = evt.which; //mozilla, opera
        } catch (e) {
            return '';
        }
    }

    // Handle numeric keypad entries
    switch (keyCode) {
        case 187: return '+';   // workaround for IE/ASV
        case 189: return '-';   // workaround for IE/ASV
        case 110: return '.';   //unused
        case 109: return '-';   //numeric keypad
        case 107: return '+';   //numeric keypad
        case 106: return '*';   //unused
        case 111: return '/';   //unused
        case 105: return '9';   //numeric keypad
        case 104: return '8';   //numeric keypad
        case 103: return '7';   //unused
        case 102: return '6';   //numeric keypad
        case 101: return '5';   //numeric keypad
        case 100: return '4';   //numeric keypad
        case 99:  return '3';   //numeric keypad
        case 98:  return '2';   //numeric keypad
        case 97:  return '1';   //numeric keypad
        case 96:  return '0';   //unused
        case 40:  return '2';   //down arrow
        case 39:  return '6';   //right arrow
        case 38:  return '8';   //up arrow
        case 37:  return '4';   //left arrow
        case 27:  return '^escape';
        case 8:   return 'backspace';
        default:  return String.fromCharCode(keyCode).toLowerCase();
    }
}

/**
 *  Callback when key is pressed down.
 */
function keyDown(evt)
{
    var svgState = getSvgState();
    var keyChar = getKeyChar(evt);

    switch (keyChar) {
        case ' ':
            // Two behavior:
            //   1. Only spacebar, then full view. (on keyup)
            //   2. Spacebar for 500ms and mouse drag, then pan.
            window.clearTimeout(svgState.spaceTimeoutID);
            svgState.spaceTimeoutID = window.setTimeout('addMousePanScrim();', 350);
            break;
        case 'p':
        case 'q':
        case '9':
            addMousePanScrim(evt);
            break;
        case 'h':
            displayById('prop.navHelp');
            break;
        case 'a':
            displayById('prop.navAbout');
            break;
        case 'f':
        case '5':
            // Shift-f zooms all to fullscreen.  Undocumented for now.
            // f zoom to fullscreen
            isShiftPressed(evt) ? fillScreenAll(evt) : fillScreen(evt);
            break;
        case '1':
            // Shift-1 zooms all to normal.  Undocumented for now.
            // 1 zoom to normal
            isShiftPressed(evt) ? zoomNormalAll(evt) : zoomNormal(evt);
            break;
        case 'd':
        case '4':
            panLeft(evt);
            break;
        case 'e':
        case '8':
            panUp(evt);
            break;
        case 'c':
        case '2':
            panDown(evt);
            break;
        case 'g':
        case '6':
            panRight(evt);
            break;
        case 'r':
        case '+':
        case '=':
            zoomIn(evt);
            break;
        case 'v':
        case '-':
            zoomOut(evt);
            break;
        case 'x':
        case '3':
            toggleExpose(evt);
            break;
        case 'backspace':
            changeSysPrev(evt);
            break;
        case '^escape':
            // clear state
            removeMousePanScrim();
            unExposeAll()
            dismissPropertyTables();
            break;
        case 't':
            // toggle property table. Undocumented for now.
            toggleShowPropertyTables();
            break;
        /*
        case 'b':
            toggleZoomBox();
                  */
        default:
            // noop
    }

    /*
    // prevent default action
    if (evt.preventDefault) {
        evt.preventDefault();
    }
    evt.returnValue = false;

    return false;
    */
}

/*
function stopDef(e) {
if (e &&e.preventDefault) e.preventDefault();
else if (window.event && window.event.returnValue)
window.eventReturnValue = false;
}
*/
/*
function toggleZoomBox(evt)
{
    var svgState = getSvgState();
    var scrim = findScrimElement(currCanvas, currSys);

    // Get the current canvas
    var currSys = svgState.currSys;
    var currCanvas = svgState.currSysCanvas;

    if (svgState.isZoomBox)
    {
        dismissPropertyTables(currCanvas);

        // Get the original viewbox, and parse into a numeric array
        var vbOrig = currCanvas.getAttributeNS(null, 'original_viewBox');
        var vbArray = new Array();
        if (vbOrig)
        {
            vbArray = vbOrig.split(' ');
            vbArray[3] = parseFloat(vbArray[3]);
            vbArray[2] = parseFloat(vbArray[2]);
            vbArray[1] = parseFloat(vbArray[1]);
            vbArray[0] = parseFloat(vbArray[0]);
        }
        else
        {
            // No original view box.
            vbArray[3] = 800;
            vbArray[2] = 600;
            vbArray[1] = 0;
            vbArray[0] = 0;
        }

        // Find the scrim element
        var scrim = findScrimElement(currCanvas, currSys);

        // Add some padding to enclose the entire window
        var scrimPad = 4096;

        // Set the scrim size
        scrim.setAttributeNS(null, 'x', vbArray[0] - scrimPad);
        scrim.setAttributeNS(null, 'y', vbArray[1] - scrimPad);
        scrim.setAttributeNS(null, 'width', vbArray[2] - vbArray[0] + 2*scrimPad);
        scrim.setAttributeNS(null, 'height', vbArray[3] - vbArray[1] + 2*scrimPad);

        // Set the scrim color
        scrim.setAttributeNS(null, 'fill', 'rgb(0%,10%,0%)');
        scrim.setAttributeNS(null, 'fill-opacity', '.04');

        // Set the scrim events
        scrim.setAttributeNS(null, 'onmousedown', 'zoomBoxMouseDown(evt)');
        scrim.setAttributeNS(null, 'onmouseup', 'zoomBoxMouseUp(evt)');
        scrim.setAttributeNS(null, 'onmouseout', '');
        scrim.setAttributeNS(null, 'onmouseover', '');
        scrim.setAttributeNS(null, 'onmousemove', 'zoomBoxMouseMove(evt)');

        // This will consume all the events for the canvas
        scrim.setAttributeNS(null, 'pointer-events', 'all');

        // Show the scrim
        scrim.setAttributeNS(null, 'display', 'inline');

        // Add it to the current canvas
        currCanvas.appendChild(scrim);
    }
    else
    {


    }




}


function zoomBoxMouseUp(evt)
{
    var svgState = getSvgState();
    svgState.svgDoc.rootElement.removeEventListener('mousemove', zoomBoxMouseMove, false);

    alert('mouseup');

    svgState.showPropertyTables = true;
}

function zoomBoxMouseMove(evt)
{
    var zoomBox = findZoomBox();
    var zoomBoxX = parseFloat(zoomBox.getAttributeNS(null, 'startX'));
    var zoomBoxY = parseFloat(zoomBox.getAttributeNS(null, 'startY'));
    var zoomBoxWidth = evt.clientX - zoomBoxX;
    var zoomBoxHeight = evt.clientY - zoomBoxY;

    if ((zoomBoxWidth < 0) && (zoomBoxHeight < 0))
    {
        zoomBox.setAttributeNS(null, 'x', zoomBoxX + zoomBoxWidth);
        zoomBox.setAttributeNS(null, 'y', zoomBoxY + zoomBoxHeight);
        zoomBox.setAttributeNS(null, 'width', -zoomBoxWidth);
        zoomBox.setAttributeNS(null, 'height', -zoomBoxHeight);
    }
    else if (zoomBoxWidth < 0)
    {
        zoomBox.setAttributeNS(null, 'x', zoomBoxX + zoomBoxWidth);
        zoomBox.setAttributeNS(null, 'width', -zoomBoxWidth);
        zoomBox.setAttributeNS(null, 'height', zoomBoxHeight);
    }
    else if (zoomBoxHeight < 0)
    {
        zoomBox.setAttributeNS(null, 'y', zoomBoxY + zoomBoxHeight);
        zoomBox.setAttributeNS(null, 'width', zoomBoxWidth);
        zoomBox.setAttributeNS(null, 'height', -zoomBoxHeight);
    }
    else
    {
        zoomBox.setAttributeNS(null, 'width', zoomBoxWidth);
        zoomBox.setAttributeNS(null, 'height', zoomBoxHeight);
    }
}

function zoomBoxMouseDown(evt)
{
    var svgState = getSvgState();
    var zoomBox = findZoomBox();


    svgState.showPropertyTables = false;

    var prevTopLeftX = parseFloat(zoomBox.getAttributeNS(null, 'x'));
    var prevTopLeftY = parseFloat(zoomBox.getAttributeNS(null, 'y'));
    var prevBottomRightX = prevTopLeftX + parseFloat(zoomBox.getAttributeNS(null, 'width'));
    var prevBottomRightY = prevTopLeftY + parseFloat(zoomBox.getAttributeNS(null, 'height'));

    svgState.svgDoc.rootElement.addEventListener('mousemove', zoomBoxMouseMove, false);


    if ((prevTopLeftX < evt.clientX) && (prevBottomRightX > evt.clientX)
       && (prevTopLeftY < evt.clientY) && (prevBottomRightY > evt.clientY))
    {
        setZoomBoxView();
    }
    else
    {
        zoomBox.setAttributeNS(null, 'startX', evt.clientX);
        zoomBox.setAttributeNS(null, 'startY', evt.clientY);

        zoomBox.setAttributeNS(null, 'x', evt.clientX);
        zoomBox.setAttributeNS(null, 'y', evt.clientY);
        zoomBox.setAttributeNS(null, 'width', 0);
        zoomBox.setAttributeNS(null, 'height', 0);
        zoomBox.setAttributeNS(null, 'display', 'inline');
    }


}

function setZoomBoxView()
{
    var svgState = getSvgState();
    var zoomBox = findZoomBox();

    var newViewBox = new Array();
    var zoomBoxX = parseFloat(zoomBox.getAttributeNS(null, 'x'));
    var zoomBoxY = parseFloat(zoomBox.getAttributeNS(null, 'y'));
    var zoomBoxWidth = parseFloat(zoomBox.getAttributeNS(null, 'width'));
    var zoomBoxHeight = parseFloat(zoomBox.getAttributeNS(null, 'height'));

    var localTopLeft = getLocalCoords(zoomBoxX, zoomBoxY);
    var localBottomRight = getLocalCoords((zoomBoxX + zoomBoxWidth),
                                          (zoomBoxY + zoomBoxHeight));

    newViewBox[0] = localTopLeft[0];
    newViewBox[1] = localTopLeft[1];
    newViewBox[2] = localBottomRight[0] - localTopLeft[0];
    newViewBox[3] = localBottomRight[1] - localTopLeft[1];
    svgState.currSysCanvas.setAttributeNS(null, 'viewBox', newViewBox.join(' '));

    zoomBox.setAttributeNS(null, 'display', 'none');
    zoomBox.setAttributeNS(null, 'x', 0);
    zoomBox.setAttributeNS(null, 'y', 0);
    zoomBox.setAttributeNS(null, 'width', 0);
    zoomBox.setAttributeNS(null, 'height', 0);
}

*/

/**
 *  Mouse scroll wheel callback
 */
function wheel(evt)
{
    var delta = 0;
    if (!evt) {
        evt = window.event;
    }
    if (evt.wheelDelta) {
        delta = evt.wheelDelta/120;
        if (evt.opera) { delta = -delta; }
    }
    else if (evt.detail) {
        delta = -evt.detail/3;
    }

    if (delta) {
        if (delta < 0) {
            zoomOut(evt);
        } else {
            zoomIn(evt);
        }

        if (evt.preventDefault) {
            evt.preventDefault();
        }
        evt.returnValue = false;
    }

    // prevent default action
    return false;
}

/**
 *  Checks if the shift key is pressed.
 */
function isShiftPressed(evt)
{
    if (evt.modifiers) {
        return false; //pre-mozilla netscape, not supported
    } else {
        return evt.shiftKey;
    }
}

/**
 *  Callback when key is released.
 */
function keyUp(evt)
{
    var svgState = getSvgState();
    var keyChar = getKeyChar(evt);

    switch (keyChar) {
        case ' ':
            // Clear out the mouse pan scrim
            window.clearTimeout(svgState.spaceTimeoutID);
            // If mouse scim was ever created, then do not fill screen
            if (!svgState.spaceMousePanScrimAdded) {
                isShiftPressed(evt) ? fillScreenAll(evt) : fillScreen(evt);
            }
            svgState.spaceMousePanScrimAdded = false;
        case 'p':
        case 'q':
        case '9':
            svgState.spaceMousePanScrimAdded = false;
            removeMousePanScrim();
            break;
        case 'h':
            dismissById('prop.navHelp');
            break;
        case 'a':
            dismissById('prop.navAbout');
            break;
        default:
            /* noop */
    }

    /*
    // stop default action
    if (evt.preventDefault)
    {
        evt.preventDefault();
    }
    evt.returnValue = false;

    // prevent default action
    return false;
    */
}

/**
 *  The Adobe SVG plug-in provides a special field "contextMenu" which is
 *  a DOM document containing information about the viewer plug-in.  It
 *  can be customized, which we are doing here.
 */
function customizeContextMenu(evt)
{
    if (!window.contextMenu)
    {
        return;
    }

    var menuElement = window.contextMenu.getDocumentElement();
    var childEl = menuElement.getFirstChild();
    while (childEl)
    {
        menuElement.removeChild(childEl);
        childEl = menuElement.getFirstChild();
    }

    var m = window.contextMenu.createElement('Header');
    m.appendChild(window.contextMenu.createTextNode('Simulink Web Viewer'));
    menuElement.appendChild(m);

    var svgState = getSvgState();
    var jaFlag = (svgState.lang == "ja");

    menuElement.appendChild(createContextMenuItem('zoomIn(evt)','zoomIn',(jaFlag ? '\u30BA\u30FC \u30E0\u30A4\u30F3 (&R)' : 'Zoom in (&R)')));
    menuElement.appendChild(createContextMenuItem('zoomOut(evt)','zoomOut',(jaFlag ? '\u30BA\u30FC\u30E0 \u30A2\u30A6\u30C8 (&V)' : 'Zoom out (&V)')));
    menuElement.appendChild(createContextMenuItem('fillScreen(evt)','fillScreen',(jaFlag ? '\u30D5\u30EB\u30B9\u30AF\u30EA\u30FC\u30F3\u306B\u62E1\u5927 (&F)' : 'Zoom to full screen (&F)')));
    menuElement.appendChild(createContextMenuItem('toggleMousePanScrim(evt)','toggleMousePanScrim',(jaFlag ? '\u30DE\u30A6\u30B9\u3067\u56DE\u8EE2 (&P)' : 'Pan with mouse (&P)')));
    menuElement.appendChild(createContextMenuItem('toggleExpose(evt)','toggleExpose',(jaFlag ? '\u3059\u3079\u3066\u306E\u30EC\u30A4\u30E4\u30FC\u3092\u8868\u793A (&X)' : 'Show all layers (&X)')));

    menuElement.appendChild(window.contextMenu.createElement('separator'));

    menuElement.appendChild(createContextMenuItemBuiltin('Find','Find',(jaFlag ? '\u30C6\u30AD\u30B9\u30C8\u306E\u691C\u7D22' : 'Find text')));
    menuElement.appendChild(createContextMenuItemBuiltin('Copy','Copy',(jaFlag ? '\u30C6\u30AD\u30B9\u30C8\u306E\u30B3\u30D4\u30FC' : 'Copy text')));

    menuElement.appendChild(window.contextMenu.createElement('separator'));

    menuElement.appendChild(createContextMenuItemBuiltin('OriginalView','OriginalView',(jaFlag ? '\u8868\u793A\u306E\u30EA\u30BB\u30C3\u30C8' : 'Reset view')));
    menuElement.appendChild(createContextMenuItemBuiltin('About','About',(jaFlag ? '\u30D7\u30E9\u30B0\u30A4\u30F3\u306B\u3064\u3044\u3066...' : 'About plugin...')));
}

/**
 *  Create a context menu which defines callbacks as custom javascript functions
 */
function createContextMenuItem(onActivate, id, textLabel)
{
    var m = window.contextMenu.createElement('item');
    m.setAttributeNS(null, 'onactivate', onActivate);
    m.setAttributeNS(null, 'id', id);
    m.appendChild(window.contextMenu.createTextNode(textLabel));
    return m;
}

/**
 *  Create a context menu which defines callbacks built-in functions
 */
function createContextMenuItemBuiltin(action, id, textLabel)
{
    var m = window.contextMenu.createElement('item');
    m.setAttributeNS(null, 'action', action);
    m.setAttributeNS(null, 'id', id);
    m.appendChild(window.contextMenu.createTextNode(textLabel));
    return m;
}

/*============================================================================
 * Show All Layers
 *============================================================================*/
/**
 * Hide current system, then show all systems in a rectangular grid
 */
function exposeAll()
{
    var svgState = getSvgState();
    if (svgState.isShowingAllCanvas) {
        return;
    }
    svgState.isShowingAllCanvas = true;

    //    NOTE* The following call MUST be made before the frameset is resized.  Doing so afterwards can result in a 
    //        negative wHeight value (since the frame change temporarily destroys the window)
    var dim = getBrowserInnerWindowDimensions();
    var wWidth  = dim[0];
    var wHeight = dim[1];

    var frameset = top.document.getElementById(gFrameID.frameset_model);
    if (frameset) {
        frameset.rows = "100%,0%";
    }

    var currCanvas = svgState.currSysCanvas;
    if (currCanvas) {
        dismissPropertyTables(currCanvas);
        removeMousePanScrim();
    }

    // Calculate the square box to fit each system in a rectangular grid
    var allSystems  = findCanvasAll();
    var canvasCount = gNumSys; //allSystems.length;
    var canvasEdge  = Math.min(144, Math.sqrt(wWidth*wHeight/canvasCount)); //upper bound
    var rowCount    = Math.ceil(wHeight/canvasEdge);
    var colCount    = Math.ceil(wWidth/canvasEdge);
    canvasEdge      = Math.min(wHeight/rowCount, wWidth/colCount);

    // Indices that determine grid position
    var squareX = 0;
    var squareY = 0;


    var thumbnailGroup = svgState.thumbnailGroup;

    var imageNode = null;
    var groupNode = null;

    svgState.canvasGroup.setAttribute('display','none');
    svgState.currSysCanvas.setAttribute('display','none');

    if (svgState.addedThumbs) {
        svgState.thumbnailGroup.setAttribute('display','inline');
        return;
    }

    for (var id in gIDMap)
    {
        groupNode = thumbnailGroup.ownerDocument.createElementNS(gSVGNS,'g');
        groupNode.setAttribute('pointer-events','all');
        groupNode.setAttribute('onmouseover','scrimHighlight(evt)');
        groupNode.setAttribute('onmouseout','scrimUnhighlight(evt)');
        groupNode.setAttribute('onmousedown','');
        groupNode.setAttribute('onmouseup','');
        groupNode.setAttribute('onclick','unExposeAll("' + escapeCharacters(id) + '")');
        groupNode.setAttribute('id', 'group.thumbnail.' + id);

        imageNode = thumbnailGroup.ownerDocument.createElementNS(gSVGNS,'image');
        imageNode.setAttribute('x',squareX*canvasEdge+5);
        imageNode.setAttribute('y',squareY*canvasEdge+5);
        imageNode.setAttribute('width',canvasEdge-10);
        imageNode.setAttribute('height',canvasEdge-10);
        imageNode.setAttribute('id', 'thumbnail.' + id);
        imageNode.setAttributeNS(gXLINKNS, 'xlink:href',gIDMap[id].thumb);

        scrim = thumbnailGroup.ownerDocument.createElementNS(gSVGNS,'rect');
        scrim.setAttribute('id', 'scrim.' + id);
        scrim.setAttribute('fill-opacity','0');
        scrim.setAttribute('x', squareX*canvasEdge);
        scrim.setAttribute('y', squareY*canvasEdge);
        scrim.setAttribute('width', canvasEdge);
        scrim.setAttribute('height', canvasEdge);;
        scrim.setAttribute('fill', 'rgb(0%,255%,255%)');
        scrim.setAttribute('fill-opacity', '0');
        scrim.setAttribute('display', 'inline');
        scrim.setAttribute('cursor', 'pointer');

        groupNode.appendChild(imageNode);
        groupNode.appendChild(scrim);
        thumbnailGroup.appendChild(groupNode);

        // Determine grid indices
        if (squareX == (colCount - 1)) {
            squareX = 0;
            squareY++;
        } else {
            squareX++;
        }
    }

    svgState.addedThumbs = true;

    setTitleText('Show all layers. Select a layer or press "X" to cancel.','\u3059\u3079\u3066\u306E\u30EC\u30A4\u30E4\u30FC\u3092\u8868\u793A. \u30EC\u30A4\u30E4\u3092\u9078\u629E\u3059\u308B\u304B\u3001\u30AD\u30E3\u30F3\u30BB\u30EB\u3059\u308B\u305F\u3081\u306B "X" \u3092\u62BC\u3057\u3066\u304F\u3060\u3055\u3044\u3002');  //*JA*
}

/**
 * Go from viewing all systems to a single system.  If sysName is not specified
 * then show the current system.
 */
function unExposeAll(sysName)
{
    var svgState = getSvgState();
    if (!svgState.isShowingAllCanvas) {
        return;
    }
    svgState.isShowingAllCanvas = false;

    svgState.canvasGroup.setAttribute('display','inline');
    svgState.thumbnailGroup.setAttribute('display','none');

    // If sysName is not defined then get the current System
    if (!sysName) {
        sysName = svgState.currSys;
    }

    // Show the single system
    changeSysByName(sysName, false);
}

/**
 *  Toggle between showing the current system or all systems
 */
function toggleExpose()
{
    var svgState = getSvgState();
    if (svgState.isShowingAllCanvas) {
        unExposeAll();
    } else {
        exposeAll();
    }
}

/**
 *  Highlights the scrim rectangle during a onmouseover event.
 */
function scrimHighlight(evt)
{
    // Highlight the scrim rectangle


    var id = getCurrentTargetId(evt);
    var sysName = id.substring(16);

    var imageNode = findChildById(evt.currentTarget, 'thumbnail.' + sysName);

    imageNode.setAttribute('x', parseFloat(imageNode.getAttribute('x')) - 5);
    imageNode.setAttribute('y', parseFloat(imageNode.getAttribute('y')) - 5);
    imageNode.setAttribute('height', parseFloat(imageNode.getAttribute('height')) +10);
    imageNode.setAttribute('width', parseFloat(imageNode.getAttribute('width')) + 10);


    var scrim = findChildById(evt.currentTarget, 'scrim.' + sysName);

    scrim.setAttribute('fill-opacity', '.1');

    // Update the title TODO
    //updateTitle(evt.target.parentNode);

    setTitleText(sysName);

    // Get the full system name off the scrim id by trimming off "group.thumbnail."
    var sysName = id.substring(16);

    // Highlight the tree node.
    var svgState = getSvgState();
    var tree = svgState.tree;


    if (tree) {
        var treeNodeID = tree.getIDByTitle(sysName);
        tree.highlightTo(treeNodeID, true);
    }
}

/**
 *  Unhighlights the scrim rectangle during a onmouseout event.
 */
function scrimUnhighlight(evt)
{
    // Highlight the scrim rectangle
    var id = getCurrentTargetId(evt);
    var sysName = id.substring(16);

    var imageNode = findChildById(evt.currentTarget, 'thumbnail.' + sysName);
    imageNode.setAttribute('x', parseFloat(imageNode.getAttribute('x')) + 5);
    imageNode.setAttribute('y', parseFloat(imageNode.getAttribute('y')) + 5);
    imageNode.setAttribute('height', parseFloat(imageNode.getAttribute('height')) - 10);
    imageNode.setAttribute('width', parseFloat(imageNode.getAttribute('width')) - 10);

    var scrim = findChildById(evt.currentTarget, 'scrim.' + sysName);

    scrim.setAttribute('fill-opacity', '0');


    // Unhighlight the tree
    var svgState = getSvgState();
    var tree = svgState.tree;
    if (tree) {
        tree.unhighlight();
    }
}

/*============================================================================
 * Zooming
 *============================================================================*/
// Zoom normal padding, used to prevent clipping during panning
var gZN_PAD = 1024;

/**
 *  Resize specified canvas to fit the entire browser window or frame
 */
function fillScreenByCanvas(thisCanvas)
{
    var svgState = getSvgState();
    if (thisCanvas && !svgState.isShowingAllCanvas) {
        var vbOrig = thisCanvas.getAttributeNS(null, 'original_viewBox');
        if (vbOrig) {
            // Get browser window size.
            var dim = getBrowserInnerWindowDimensions();
            var winHeight = dim[1];

            // Browser window already adjust for nav toolbar.
            // Undo that adjustment.
            var unAdjustedWinHeight = winHeight + gNavToolbarHeight;

            // Calculate the zoom without the nav toolbar
            var zHeight = 100*(winHeight/unAdjustedWinHeight) + '%';

            dismissPropertyTables(thisCanvas);
            thisCanvas.setAttributeNS(null, 'viewBox', vbOrig);
            thisCanvas.setAttributeNS(null, 'height', zHeight);
            thisCanvas.setAttributeNS(null, 'width', '100%');
        }
    }
}

/**
 *  Resize current canvas to fit the entire browser window or frame
 */
function fillScreen(evt)
{
    var svgState = getSvgState();
    fillScreenByCanvas(svgState.currSysCanvas);
}

/**
 *  Resize all canvases to fit the entire browser window or frame
 */
function fillScreenAll(evt)
{
    var svgElements = findCanvasAll();
    var canvasCount = svgElements.length;
    for (var canvasIdx = 0; canvasIdx < canvasCount; canvasIdx++)
    {
        var thisCanvas = svgElements.item(canvasIdx);
        fillScreenByCanvas(thisCanvas);
    }
    setTitleText("Zoom to full screen (all layers)", "\u30D5\u30EB\u30B9\u30AF\u30EA\u30FC\u30F3\u306B\u62E1\u5927 (\u3059\u3079\u3066\u306E\u30EC\u30A4\u30E4)"); //*JA*
}

/**
 *  Resize specified canvas to a specified zoom in per cent
 */
function zoomAbsoluteByCanvas(thisCanvas, zoomFactor)
{
    var svgState = getSvgState();

    if (thisCanvas && !svgState.isShowingAllCanvas) {
        // Get orginal viewbox
        var vbOrig = thisCanvas.getAttributeNS(null, 'original_viewBox');
        if (vbOrig) {
            var vbArray = new Array();
            vbArray = vbOrig.split(' ');
            vbArray[3] = parseFloat(vbArray[3]);
            vbArray[2] = parseFloat(vbArray[2]);
            vbArray[1] = parseFloat(vbArray[1]);
            vbArray[0] = parseFloat(vbArray[0]);

            // Determine width and height.  Also add some padding
            thisCanvas.setAttributeNS(null, 'width' ,
                zoomFactor*(vbArray[2] - vbArray[0]) + gZN_PAD);
            thisCanvas.setAttributeNS(null, 'height',
                zoomFactor*(vbArray[3] - vbArray[1]) + gZN_PAD);

            // Add padding to the view box width and height
            vbArray[2] = (vbArray[2] - vbArray[0]) + gZN_PAD/zoomFactor;
            vbArray[3] = (vbArray[3] - vbArray[1]) + gZN_PAD/zoomFactor;

            // Set the size via the viewbox.
            thisCanvas.setAttributeNS(null, 'viewBox', vbArray.join(' '));
        }
    }
}

/**
 *  Resize current canvas to 100%
 */
function zoomNormal(evt)
{
    var svgState = getSvgState();
    zoomAbsoluteByCanvas(svgState.currSysCanvas, 1);
    return false;
}

/**
 *  Resize all canvases to 100%  @BUG: No longer works for incremental loading
 */
function zoomNormalAll(evt)
{
    var svgElements = findCanvasAll();
    var canvasCount = svgElements.length;
    for (var canvasIdx = 0; canvasIdx < canvasCount; canvasIdx++)
    {
        var thisCanvas = svgElements.item(canvasIdx);
        zoomAbsoluteByCanvas(thisCanvas, 1);
    }
    setTitleText("Zoom to 100% (all layers)","100% \u306B\u62E1\u5927 (all layers)"); //*JA*
}

/**
 *  Resize current canvas based on its current zoom level
 */
function zoomRelative(zoomFactor, evt)
{
    var svgState = getSvgState();
    var currCanvas = svgState.currSysCanvas;

    if (currCanvas && !svgState.isShowingAllCanvas) {
        dismissPropertyTables(currCanvas);

        // Get current viewbox, and convert it into a numerical array
        var vbCurr = currCanvas.getAttributeNS(null, 'viewBox');
        if (!vbCurr) {
            vbCurr = currCanvas.getAttributeNS(null, 'original_viewBox');
        }
        vbCurrArray = new Array();
        vbCurrArray = vbCurr.split(' ');
        vbCurrArray[3] = parseFloat(vbCurrArray[3]);
        vbCurrArray[2] = parseFloat(vbCurrArray[2]);
        vbCurrArray[1] = parseFloat(vbCurrArray[1]);
        vbCurrArray[0] = parseFloat(vbCurrArray[0]);

        // Check width to determine units
        var currWidth = currCanvas.getAttributeNS(null, 'width');
        if (currWidth && (currWidth.indexOf('%') == -1)) {
            // Width and height specified in pixels
            // Get original viewbox, and convert it into a numerical array
            var vbOrig = currCanvas.getAttributeNS(null, 'original_viewBox');
            var vbOrigArray = new Array();
            vbOrigArray = vbOrig.split(' ');
            vbOrigArray[3] = parseFloat(vbOrigArray[3]);
            vbOrigArray[2] = parseFloat(vbOrigArray[2]);
            vbOrigArray[1] = parseFloat(vbOrigArray[1]);
            vbOrigArray[0] = parseFloat(vbOrigArray[0]);

            // Calculate new viewbox width and height
            vbCurrArray[3] = vbOrigArray[3] + (vbCurrArray[3] - vbOrigArray[3])/zoomFactor;
            vbCurrArray[2] = vbOrigArray[2] + (vbCurrArray[2] - vbOrigArray[2])/zoomFactor;

            // Calculate new width and add some padding
            var actualWidth = parseFloat(currWidth) - gZN_PAD;
            currCanvas.setAttributeNS(null, 'width', zoomFactor*actualWidth + gZN_PAD);

            // Calculate new height and add some padding
            var currHeight = currCanvas.getAttributeNS(null, 'height');
            var actualHeight = parseFloat(currHeight) - gZN_PAD;
            currCanvas.setAttributeNS(null, 'height', zoomFactor*actualHeight + gZN_PAD);

        } else {
            // Width and height specified in percentages
            vbCurrArray[3] = vbCurrArray[3]/zoomFactor;
            vbCurrArray[2] = vbCurrArray[2]/zoomFactor;
        }

        var useMousePos = true;
        if (navigator.appName == 'Netscape') {
            // Firefox 2 and earlier can not do mouse centered zooming.  See this bug report
            // https://bugzilla.mozilla.org/show_bug.cgi?id=352179
            var userAgent = navigator.userAgent;
            useMousePos = (parseFloat(userAgent.substring(userAgent.lastIndexOf('/') + 1)) > 2);
        }

        // Get Mouse position in local coordinates
        //var winDim = getBrowserInnerWindowDimensions();
        var mouseX = 0;//winDim[0]/2;
        var mouseY = 0;//winDim[1]/2;
        if (useMousePos && evt && evt.clientX) {
            mouseX = evt.clientX;
            mouseY = evt.clientY;
        }
        var beforeLocalCoords = getLocalCoords(mouseX, mouseY);

        // Get local coords after the zoom.  Note.  Zoom is not done yet.
        var afterVisViewBox = getVisibleViewBox(currCanvas, vbCurrArray.join(' '));
        var afterLocalCoords = getLocalCoords(mouseX, mouseY, afterVisViewBox);

        // Adjust offset so local position does not move
        vbCurrArray[0] = vbCurrArray[0] - (afterLocalCoords[0] - beforeLocalCoords[0]);
        vbCurrArray[1] = vbCurrArray[1] - (afterLocalCoords[1] - beforeLocalCoords[1]);

        // Set the size via the viewbox.
        currCanvas.setAttributeNS(null, 'viewBox', vbCurrArray.join(' '));
    }
}

/**
 *  Zoom in to 110%
 */
function zoomIn(evt)
{
    zoomRelative(1.1, evt);
}

/**
 *  Zoom out to 90%
 */
function zoomOut(evt)
{
    zoomRelative(0.9, evt);
}

/*============================================================================
 * Panning
 *============================================================================*/

/**
 * vbIdx can be 0 or 1.  When 0, operate on vb[0] and vb[2] (horizontal)
 * direction can be -1 or 1.  When positive, shift away from origin.
 */
function panRelative(evt, vbIdx, direction)
{
    var svgState = getSvgState();
    var currCanvas = svgState.currSysCanvas;

    if (currCanvas && !svgState.isShowingAllCanvas)
    {
        var vbCurr = currCanvas.getAttributeNS(null, 'viewBox');
        if (!vbCurr)
        {
            vbCurr = currCanvas.getAttributeNS(null, 'original_viewBox');
        }
        if (vbCurr)
        {
            dismissPropertyTables(currCanvas);

            // Split current viewbox into an array
            var vbArray = new Array();
            vbArray = vbCurr.split(' ');

            // Determine how much to shift
            var shiftBase = new Number();
            var currWidth = currCanvas.getAttributeNS(null, 'width');
            if (currWidth && (currWidth.indexOf('%') == -1))
            {
                // Width and height specified in pixels.  Get the original
                // viewbox height/width to determine how much to shift.
                var vbOrig = currCanvas.getAttributeNS(null, 'original_viewBox');
                var vbOrigArray = new Array();
                vbOrigArray = vbOrig.split(' ');
                shiftBase = parseFloat(vbOrigArray[2 + vbIdx]);
            }
            else
            {
                // Width and height specified in percentages.  Get the current
                // viewbox height/width to determine how much to shift.
                shiftBase = parseFloat(vbArray[2 + vbIdx]);
            }

            // Shift it by changing the top-left hand corner
            vbArray[0 + vbIdx] = parseFloat(vbArray[0 + vbIdx]) +
                direction*(shiftBase/50);

            // Set the shift via the viewbox
            currCanvas.setAttributeNS(null, 'viewBox', vbArray.join(' '));
        }
    }
}

/**
 *  Pan up
 */
function panUp(evt)
{
    panRelative(evt, 1, 1);
}

/**
 *  Pan down
 */
function panDown(evt)
{
    panRelative(evt, 1, -1);
}

/**
 *  Pan left
 */
function panLeft(evt)
{
    panRelative(evt, 0, 1);
}

/**
 *  Pan down
 */
function panRight(evt)
{
    panRelative(evt, 0, -1);
}

/**
 *  Toggle between adding and removing the mouse pan scrim.  Called by the
 *  context menu.
 */
function toggleMousePanScrim(evt)
{
    var svgState = getSvgState();
    if (svgState.dragMode)
    {
        removeMousePanScrim();
    }
    else
    {
        addMousePanScrim(evt, 'Pan with mouse.  Press "P" to resume normal viewing.', '\u30DE\u30A6\u30B9\u3067\u79FB\u52D5  \u6A19\u6E96\u8868\u793A\u306B\u623B\u308B\u306B\u306F "P" \u3092\u62BC\u3057\u3066\u304F\u3060\u3055\u3044\u3002');
    }
}

/**
 *  Add a scrim to indicate mouse pan mode.  ASV3 does not allow us to change
 *  mouse pointer.  Will use a scrim to indicate mouse pan mode.
 */
function addMousePanScrim(evt, engStatus, jaStatus)
{
    var svgState = getSvgState();
    if (svgState.dragMode || svgState.isShowingAllCanvas)
    {
        // Already have a mouse pan scrim or we are showing all systems
        return;
    }

    // Set drag mode
    svgState.dragMode = true;

    // Used during space keydown event to detect if a mouse pan was ever added.
    // Cleared on space keyup event
    svgState.spaceMousePanScrimAdded = true;

    // Get the current canvas
    var currSys = svgState.currSys;
    var currCanvas = svgState.currSysCanvas;


    if (currCanvas)
    {
        dismissPropertyTables(currCanvas);

        // Get the original viewbox, and parse into a numeric array
        var vbOrig = currCanvas.getAttributeNS(null, 'original_viewBox');
        var vbArray = new Array();
        if (vbOrig)
        {
            vbArray = vbOrig.split(' ');
            vbArray[3] = parseFloat(vbArray[3]);
            vbArray[2] = parseFloat(vbArray[2]);
            vbArray[1] = parseFloat(vbArray[1]);
            vbArray[0] = parseFloat(vbArray[0]);
        }
        else
        {
            // No original view box.
            vbArray[3] = 800;
            vbArray[2] = 600;
            vbArray[1] = 0;
            vbArray[0] = 0;
        }

        // Find the scrim element
        var scrim = findScrimElement(currCanvas, currSys);


        // Add some padding to enclose the entire window
        var scrimPad = 4096;

        // Set the scrim size
        scrim.setAttributeNS(null, 'x', vbArray[0] - scrimPad);
        scrim.setAttributeNS(null, 'y', vbArray[1] - scrimPad);
        scrim.setAttributeNS(null, 'width', vbArray[2] - vbArray[0] + 2*scrimPad);
        scrim.setAttributeNS(null, 'height', vbArray[3] - vbArray[1] + 2*scrimPad);

        // Set the scrim color
        scrim.setAttributeNS(null, 'fill', 'rgb(0%,0%,0%)');
        scrim.setAttributeNS(null, 'fill-opacity', '.04');

        // Set the scrim events
        scrim.setAttributeNS(null, 'onmousedown', 'startMousePan(evt)');
        scrim.setAttributeNS(null, 'onmouseup', 'endMousePan(evt)');
        scrim.setAttributeNS(null, 'onmouseout', 'endMousePan(evt)');
        scrim.setAttributeNS(null, 'onmouseover', '');

        // Set the mouse pointer
        scrim.setAttributeNS(null, 'cursor', 'move'); // not working in ASV3

        // This will consume all the events for the canvas
        scrim.setAttributeNS(null, 'pointer-events', 'all');

        // Show the scrim
        scrim.setAttributeNS(null, 'display', 'inline');

        // Add it to the current canvas
        currCanvas.appendChild(scrim);

        // Get default title text.  Used when pressing the spacebar or 'P' key
        if (!engStatus)
        {
            engStatus = 'Pan with mouse.  Release key to resume normal viewing.';
        }
        if (!jaStatus)
        {
            jaStatus = '\u30DE\u30A6\u30B9\u3067\u79FB\u52D5  \u6A19\u6E96\u8868\u793A\u306B\u623B\u308B\u306B\u306F\u30AD\u30FC\u3092\u653E\u3057\u3066\u304F\u3060\u3055\u3044\u3002';
        }

        // Update the title
        setTitleText(engStatus, jaStatus);
    }
}

/**
 *  Remove scrim to indicate mouse pan mode ened.
 */
function removeMousePanScrim()
{
    var svgState = getSvgState();
    var scrim = findScrimElement(svgState.currSysCanvas, svgState.currSys);
    if (scrim) {
        scrim.setAttributeNS(null, 'display', 'none');
        scrim.setAttributeNS(null, 'pointer-events', 'none');
    }

    // Update title to show current system
    updateTitle(0);

    // Set drag mode
    svgState.dragMode = false;
}

// Global variable used to track panning.  No need to put them in a state
// object because they will always operate in the same context.
var gDragStartX = 0;
var gDragStartY = 0;
var gDragStartViewBox = 0;
var gDragStartWidth = 0;
var gDragStartHeight = 0;

/**
 *  Start mousepan.  Call onmousedown callback.
 */
function startMousePan(evt)
{
    // Get current canvas
    var svgState = getSvgState();
    var currCanvas = svgState.currSysCanvas;
    if (currCanvas && !svgState.isShowingAllCanvas)
    {
        gDragStartX = evt.clientX;
        gDragStartY = evt.clientY;

        // Get the current viewbox
        var vbCurr = currCanvas.getAttributeNS(null, 'viewBox');
        if (!vbCurr)
        {
            vbCurr = currCanvas.getAttributeNS(null, 'original_viewBox');
        }
        gDragStartViewBox = new Array();
        gDragStartViewBox = vbCurr.split(' ');
        gDragStartViewBox[0] = parseFloat(gDragStartViewBox[0]);
        gDragStartViewBox[1] = parseFloat(gDragStartViewBox[1]);
        gDragStartViewBox[2] = parseFloat(gDragStartViewBox[2]);
        gDragStartViewBox[3] = parseFloat(gDragStartViewBox[3]);

        // Get size of the canvas so we can translate screen units to the local
        // coordinate system
        gDragStartWidth = currCanvas.getAttributeNS(null, 'width');
        gDragStartHeight = currCanvas.getAttributeNS(null, 'height');

        if (gDragStartWidth && (gDragStartWidth.indexOf('%') != -1))
        {
            // Height and width are specified in percentage.  Use the browser
            // dimensions to determine actual size.  This assumes height and
            // width are both specified in percentages.
            var browserDim = getBrowserInnerWindowDimensions();
            gDragStartWidth = browserDim[0];

            // We need to maintain the aspect ratio.  Will correct on the
            // height since it is not at 100%.
            var aspectRatio = gDragStartViewBox[3]/gDragStartViewBox[2];
            gDragStartHeight = aspectRatio*gDragStartWidth;
        }
        else
        {
            // Height and width are specified in pixels.
            gDragStartWidth  = parseFloat(gDragStartWidth);
            gDragStartHeight = parseFloat(gDragStartHeight);
        }

        // Set the onmousemove callback to do the actual mouse pan.
        evt.target.setAttributeNS(null, 'onmousemove', 'doMousePan(evt)');
    }
}

/**
 *  At the end of panning.
 */
function endMousePan(evt)
{
    // Remove onmousemove listener

    evt.target.setAttributeNS(null, 'onmousemove', '');

    // Reset global var
    gDragStartX = 0;
    gDragStartY = 0;
    gDragStartViewBox = 0;
    gDragStartWidth = 0;
    gDragStartHeight = 0;
}

/**
 *  Do the mouse pan
 */
function doMousePan(evt)
{
    var posY = evt.clientY;
    var posX = evt.clientX;

    var svgState = getSvgState();
    var currCanvas = svgState.currSysCanvas;
    if (currCanvas && !svgState.isShowingAllCanvas)
    {
        var newXo = gDragStartViewBox[0] -
            (posX - gDragStartX)*gDragStartViewBox[2]/gDragStartWidth;
        var newYo = gDragStartViewBox[1] -
            (posY - gDragStartY)*gDragStartViewBox[3]/gDragStartHeight;

        // Set the pan action via the viewbox
        currCanvas.setAttributeNS(null, 'viewBox', newXo + ' ' + newYo + ' '
            + gDragStartViewBox[2] + ' ' + gDragStartViewBox[3]);
    }
}

/*============================================================================
 * Inter-Layer Navigation
 *============================================================================*/

/**
 * Change to home system.  Adds to history.
 */
function changeSysHome(evt)
{
    var svgState = getSvgState();
    changeSysByName(svgState.homeSys,true);
}

/**
 * Change to previous system.  Does not add to history.
 */
function changeSysPrev(evt)
{
    var svgState = getSvgState();
    var prevSysName = svgState.prevSys.pop();
    changeSysByName(prevSysName,false);
}

/**
 * Change system based on the current mouse click
 */
function changeSys(evt)
{
    var sysName = getCurrentTargetLinkId(evt);
    changeSysByName(sysName,true);
}

/**
 * Change to system by name
 */
function changeSysByName(newSys,addToPrevStack)
{
    if (newSys == "") {
        return;
    }

    var svgState = getSvgState();
    var frameset = top.document.getElementById(gFrameID.frameset_model);
    if (frameset) {
        frameset.rows = "100%,0%";
    }

    var newSysCanvas = findCanvasById(newSys);
    if (newSysCanvas) {
        doChangeSys(newSys,newSysCanvas,addToPrevStack);
    } else {
        loadAndChangeSys(newSys,addToPrevStack);
    }
}

function doChangeSys(newSys,newSysCanvas,addToPrevStack)
{
    var svgState = getSvgState();

    removeMousePanScrim();
    unExposeAll();

    // If newSys is the current system and is visible then exit early.
    if (newSys == svgState.currSys) {
        if (newSysCanvas.getAttributeNS(null,"display") == "inline") {
            return;
        }
    }

    // Hide the current canvas and show new canvas
    if (svgState.currSysCanvas) {
        svgState.currSysCanvas.setAttributeNS(null,"display","none");
    }
    newSysCanvas.setAttributeNS(null,"display","inline");

    if (addToPrevStack) {
        svgState.prevSys.push(svgState.currSys);
    }

    svgState.currSys = newSys;
    svgState.currSysCanvas = newSysCanvas;

    if (svgState.tree) {
        svgState.tree.openTo(svgState.tree.getIDByTitle(newSys),true);
    }

    updateTitle(newSysCanvas);
    enableNavHome(svgState.homeSys != newSys);
    enableNavPrev(svgState.prevSys.length > 0);
 }


var gXMLHTTPRequest = false;
var gNewSys = false;
var gAddToPrevStack = false;

function loadAndChangeSys(newSys,addToPrevStack)
{
    if (newSys) {
        var svgState = getSvgState();
        var filename;
        try {
            filename = gIDMap[newSys].target;
        } catch(e) {
            return; //no-op
        }

        // If ext is not SVG or SVGZ, then open content in new frame
        var ext = filename.substring(filename.lastIndexOf("."));
        if ((ext != ".svg") && (ext != ".svgz")) {
            openLinkInWebFrame(filename);
            if(addToPrevStack) {
                svgState.prevSys.push(svgState.currSys);
            }
            svgState.currSys = newSys;
            if (svgState.tree) {
                svgState.tree.openTo(svgState.tree.getIDByTitle(newSys),true);
            }
            return;
        }

        if (typeof svgState.svgWindow.getURL == "function") {
            if (filename) {
                gNewSys = newSys;
                gAddToPrevStack = addToPrevStack;
                svgState.svgWindow.getURL(filename,changeSysByLoadingASV);
            }
        } else {
            try  {
                gXMLHTTPRequest = new XMLHttpRequest();
            } catch (e) {
                gXMLHTTPRequest = false;
            }

            if (gXMLHTTPRequest) {
                gXMLHTTPRequest.open("Get",filename,true)
                gXMLHTTPRequest.onreadystatechange = function ()
                {
                    if (gXMLHTTPRequest.readyState == 4) {
                        changeSysByLoading(newSys,addToPrevStack)
                    };
                }
                gXMLHTTPRequest.send("");
            }
        }
    }
 }

function changeSysByLoadingASV(data)
{
    var svgState = getSvgState();
    var docFrag = svgState.svgWindow.parseXML(data.content, svgState.svgDoc);
    var newSysCanvas = findChildById(docFrag, ["canvas." + gNewSys]);

    svgState.canvasGroup.appendChild(newSysCanvas);
    doChangeSys(gNewSys,newSysCanvas,gAddToPrevStack);
}

function changeSysByLoading(newSys,addToPrevStack)
{
    var svgState = getSvgState();
    var docFrag = gXMLHTTPRequest.responseXML.documentElement;
    var newSysCanvas = svgState.svgDoc.importNode(docFrag,true);

    svgState.canvasGroup.appendChild(newSysCanvas);
    doChangeSys(newSys,newSysCanvas,addToPrevStack);
}

/*============================================================================
 * Nav Buttons
 *============================================================================*/

/**
 * Enable the home button
 */
function enableNavHome(isEnabled)
{
    var svgState = getSvgState();
    if (!svgState.navHomeBtn) {
        svgState.navHomeBtn = svgState.svgDoc.getElementById("navHome");
    }
    enableNavBtn(isEnabled, svgState.navHomeBtn);
}

/**
 * Enable the previous button
 */
function enableNavPrev(isEnabled)
{
    var svgState = getSvgState();
    if (!svgState.prevSysBtn) {
        svgState.prevSysBtn = svgState.svgDoc.getElementById("navPrev");
    }
    enableNavBtn(isEnabled, svgState.prevSysBtn);
}

/**
 * Enable specified nav button
 */
function enableNavBtn(isEnabled,navBtn)
{
    if (navBtn) {
        if (isEnabled) {
            navBtn.setAttributeNS(null,"pointer-events","all");
            navBtn.setAttributeNS(null,"onmouseover","showProp(evt);highlight(evt,1)");
            navBtn.setAttributeNS(null,"onmouseout","hideProp(evt);unhighlight(evt,1)");
            navBtn.setAttributeNS(null,"stroke","rgb(0%,0%,0%)");
            navBtn.setAttributeNS(null,"cursor","pointer");
        } else {
            navBtn.setAttributeNS(null,"pointer-events","none");
            navBtn.setAttributeNS(null,"onmouseover","showProp(evt)");
            navBtn.setAttributeNS(null,"onmouseout","hideProp(evt);unhighlight(evt,1)");
            navBtn.setAttributeNS(null,"stroke","rgb(75%,75%,75%)");
            navBtn.setAttributeNS(null,"cursor","default");
        }
    }
}

/*============================================================================
 * Title Handling
 *============================================================================*/

/**
 *  Update the title for a given svg object, can be a canvas, block, system
 */
function updateTitle(thisObj)
{
    var svgState = getSvgState();
    var thisID = '';

    if (!thisObj)
    {
        // Nothing was passed in.  Used current system
        thisID = svgState.currSys;
        thisObj = svgState.currSysCanvas;
    }
    else
    {
        // Get the ID, if this a canvas then strip off leading "canvas."
        thisID = thisObj.getAttributeNS(null, 'id');
        if (thisID.substr(0,7) == 'canvas.')
        {
            thisID = thisID.substring(7);
        }
    }

    if (thisObj)
    {
        var thisTitle = findChildById(thisObj, 'title.' + thisID);
        if (thisTitle)
        {
            var titleTextNode = thisTitle.firstChild;
            if (titleTextNode)
            {
                var titleText = titleTextNode.data;
                setTitleText(titleText, titleText);
            }
        }
    }
}

/**
 *  Set the title
 */
function setTitleText(enString, jaString)
{
    var svgState = getSvgState();
    var titleTextNodeEn = svgState.titleTextNodeEn;
    var titleTextNodeJa = svgState.titleTextNodeJa;

    if (!titleTextNodeEn || !titleTextNodeJa)
    {
        // If we haven't cached the title text nodes, find them now
        var svgDoc = svgState.svgDoc;
        var titleElement = svgDoc.getElementById('navTitle');
        if (titleElement)
        {
            // There are two title node.  One is english, and the other is
            // japanese.  We use the Svg switch node to define the title
            // node.  Different languages require different font.
            var textElements = titleElement.getElementsByTagName('text');
            for (var i = 0; i < textElements.length; i++)
            {
                var thisText = textElements.item(i);
                var thisLang = thisText.getAttribute('systemLanguage');
                var cdataNode = thisText.firstChild;  //getFirstChild()
                if (!cdataNode)
                {
                    cdataNode = svgDoc.createTextNode();
                    thisText.appendChild(cdataNode);
                }

                if (thisLang == 'ja')
                {
                    titleTextNodeJa = cdataNode;
                    // cache it
                    svgState.titleTextNodeJa = titleTextNodeJa;
                }
                else
                {
                    titleTextNodeEn = cdataNode;
                    // cache it
                    svgState.titleTextNodeEn = titleTextNodeEn;
                }
            }
        }
    }

    if (titleTextNodeEn)
    {
        titleTextNodeEn.data = enString;
    }
    if (titleTextNodeJa)
    {
        if (jaString)
        {
            titleTextNodeJa.data = jaString;
        }
        else
        {
            titleTextNodeJa.data = enString;
        }
    }
}

/*============================================================================
 * Mouse Interactions
 *============================================================================*/

/**
 * Get the current target id off the mouse event
 */
function getCurrentTargetId(evt)
{
    var id = '';
    if (evt.currentTarget) {
        id = evt.currentTarget.getAttributeNS(null, 'id');
    }
    return id;
}

/**
 * Get the current target linkid off the mouse event
 */
function getCurrentTargetLinkId(evt)
{
    var linkid = '';
    if (evt.currentTarget) {
        linkid = evt.currentTarget.getAttributeNS(null, 'linkid');
    }
    return linkid;
}

/**
 * Show current target property table and highlight only if there is something
 * to link to.
 */
function showPropAndHighlight(evt)
{
    var id = getCurrentTargetId(evt);
    updateTitle(evt.currentTarget);
    showProp(evt, id);
    highlight(evt);
}

/**
 * Hide current target property table and unhighlight it
 */
function hidePropAndUnhighlight(evt)
{
    var id = getCurrentTargetId(evt);
    updateTitle(0);
    hideProp(evt, id);
    unhighlight(evt);
}

/*============================================================================
 * Property Table
 *============================================================================*/
/**
 *  Get the SVG group node holding property table information
 */
function getPropGroup(evt, id)
{
    // id is not defined when called by help button
    if (!id) {
        id = getCurrentTargetId(evt);
    }

    var prop = findSiblingByIdReverse(evt.currentTarget, 'prop.' + id);

    if (prop) {
        // Move property to the end to show on "top"
        var parentNode = prop.parentNode;
        parentNode.removeChild(prop);
        parentNode.appendChild(prop);
    }

    return prop;
}

/**
 *  Toggle between showing property tables. (not called anywhere yet)
 */
function toggleShowPropertyTables()
{
    var svgState = getSvgState();
    svgState.showPropertyTables = !svgState.showPropertyTables;
}

/**
 *  Show property table for a given id
 */
function showProp(evt, id)
{
    var svgState = getSvgState();
    if (svgState.showPropertyTables) {
        displayByElement(getPropGroup(evt, id), evt);
    }
}

/**
 *  Hide property table for a given id
 */
function hideProp(evt, id)
{
    dismissByElement(getPropGroup(evt, id));
}

/**
 *  Show property table for a given node
 */
function displayByElement(targetElement, evt)
{
    if (targetElement) {
        var p = targetElement.parentNode;
        positionPropTable(targetElement, p, evt);
        targetElement.setAttributeNS(null, 'display', 'inline');
    }
}

/**
 *  Show property table for the current target.  (see help buttons callback)
 */
function displayTarget(evt)
{
    evt.currentTarget.setAttributeNS(null, 'display', 'inline');
}

/**
 *  Show property table for the current target.  (see help key callback)
 */
function displayById(targetId)
{
    var svgState = getSvgState();
    var svgDoc = svgState.svgDoc;
    displayByElement(svgDoc.getElementById(targetId));
}

/**
 *  Hide property table for a given node.
 */
function dismissByElement(targetElement)
{
    if (targetElement) {
        targetElement.setAttributeNS(null, 'display', 'none');
    }
}

/**
 *  Hide property table for current target.  (see help buttons callback)
 */
function dismissTarget(evt)
{
    dismissByElement(evt.currentTarget);
}

/**
 *  Hide property table for a given id.  (see help key callback)
 */
function dismissById(targetId)
{
    var svgState = getSvgState();
    var svgDoc = svgState.svgDoc;
    dismissByElement(svgDoc.getElementById(targetId));
}

/**
 *  Positions the property table.
 */
function positionPropTable(targetElement, thisCanvas, evt)
{
    // Get the viewable canvas viewbox
    var vbArray = getVisibleViewBox(thisCanvas);
    if (!vbArray) {
        return;
    }

    // Get the extents
    var hThis = targetElement.getAttributeNS(null, 'extent_Height');
    if (!hThis) {
        return;
    } else {
        hThis = parseFloat(hThis);
    }
    var wThis = targetElement.getAttributeNS(null, 'extent_Width');
    if (!wThis) {
        return;
    } else {
        wThis = parseFloat(wThis);
    }

    // Get the id
    var idThis = targetElement.getAttributeNS(null, 'id');
    if (!idThis) {
        return;
    }

    // Get the preferred location
    var xThis;
    var yThis;

    if (evt && evt.clientX && evt.clientY && (idThis.indexOf('_uniq_id_') != -1)) {
        // Lines/Signals have unique IDs.  Position table right next to current mouse position
        var offsetX = 20;
        var offsetY = -5;
        var localCoords = getLocalCoords(evt.clientX + offsetX,
                                         evt.clientY + offsetY);
        xThis = localCoords[0];
        yThis = localCoords[1];
    } else {
        xThis = targetElement.getAttributeNS(null, 'preferred_X');
        if (!xThis) {
            return;
        } else {
            xThis = parseFloat(xThis);
        }

        yThis = targetElement.getAttributeNS(null, 'preferred_Y');
        if (!yThis) {
            return;
        } else {
            yThis = parseFloat(yThis);
        }
    }

    // Determine lower right coordinate.
    var rightEdge  = vbArray[0] + vbArray[2];
    var bottomEdge = vbArray[1] + vbArray[3];

    // Scaling to fit this object.
    var xScale = 1;
    var yScale = 1;

    if (hThis > 0.95*vbArray[3]) {
        // This object's height is greater than the viewbox.  Resize smaller.
        yThis  = vbArray[1] + 0.01*vbArray[3];
        yScale = vbArray[3]/hThis*0.95;
    } else {
        if ((yThis + hThis) > bottomEdge) {
            // This object's position exceeds the bottom edge.  Reposition.
            yThis = Math.max(bottomEdge - 1.01*hThis,
                             vbArray[1] + 0.01*vbArray[3]);
        }
    }

    if (wThis > 0.95*vbArray[2]) {
        // This object's width is greater than the viewbox.  Resize smaller.
        xThis  = vbArray[0] + 0.01*vbArray[2];
        xScale = vbArray[2]/wThis*0.95;
    } else {
        if ((xThis + wThis) > rightEdge) {
            // This object's position exceeds the right hand edge.  Reposition.
            xThis = Math.max(rightEdge - 1.01*wThis,
                             vbArray[0] + 0.01*vbArray[2]);
        }
    }

    var scale = Math.min(xScale, yScale);
    if (scale < 1) {
        // Move and shrink
        targetElement.setAttributeNS(null, 'transform',
            'translate('+ xThis + ',' + yThis + ') scale(' + scale + ')');
    } else {
        // Reposition only
        targetElement.setAttributeNS(null, 'transform',
            'translate('+ xThis + ',' + yThis + ')');
    }
}

/**
 *  Clears property tables AND removes filter effects
 */
function dismissPropertyTables(svgElement)
{
    var svgState = getSvgState();
    if (!svgElement) {
        svgElement = svgState.currSysCanvas;
    }

    var gElements = svgElement.getElementsByTagName('g');
    for (var i = 0; i < gElements.length; i++) {
        var gThis = gElements.item(i);
        if (gThis.getAttributeNS(null, 'id')) {
            if (gThis.getAttributeNS(null,'id').substr(0,5) == 'prop.' &&
                gThis.getAttributeNS(null,'display') == 'inline')
            {
                gThis.setAttributeNS(null,'display', 'none');
            }
            else if (gThis.getAttributeNS(null,'filter') == 'url(#highlight)')
            {
                gThis.setAttributeNS(null,'filter','none');
            }
        }
    }
}

/*============================================================================
 * Highlighting
 *============================================================================*/
/**
 * highlight(evt) will highlight only if a corresponding canvas exists
 * highlight(evt, 1) will always highlight
 */
function highlight(evt,isForce)
{
    // Get cursor attribute.
    var t = evt.currentTarget;
    var tCursor = t.getAttributeNS(null,"cursor");

    if (!tCursor) {
        // No cursor attribute.
        // Check to see if the object is linkable (once per session)
        var linkid = getCurrentTargetLinkId(evt);

        if ((isForce == 1) || gIDMap[linkid]) {
            tCursor = "pointer";
        } else {
            tCursor = "default";
        }

        // Set cursor attribute.  tCursor will not be null after first visit.
        t.setAttributeNS(null,"cursor",tCursor);
    }

    // If cursor is a pointer, then highlight
    if (tCursor == "pointer") {
        evt.currentTarget.setAttributeNS(null,"filter","url(#highlight)");
    }
}

/**
 *  Unhighlight current object.  Called from onmouseout event.
 */
function unhighlight(evt)
{
    evt.currentTarget.setAttributeNS(null,"filter","none");
}

/**
 *  Highlight help key.  Called from onmouseover event.
 */
function highlightHelpKey(evt, whichKey)
{
    var keyRect = findChildById(evt.currentTarget,"helpkey."+whichKey);
    if (keyRect) {
        keyRect.setAttributeNS(null,"filter","url(#highlight)");
        keyRect.setAttributeNS(null,"cursor","pointer");
    }
 }

/**
 *  Unhighlight help key.  Called from onmouseout event.
 */
function unhighlightHelpKey(evt, whichKey)
{
    var keyRect = findChildById(evt.currentTarget,"helpkey."+whichKey);
    if (keyRect) {
        keyRect.setAttributeNS(null,"filter","none");
    }
}

/**
 *  Highlight text (change to color blue to match Simulink behavior).  Called from onmouseover event.
 */
function highlightLink(evt)
{
    var groupNode = evt.currentTarget;
    var textNodes = groupNode.getElementsByTagName("text");

    for (i=0;i<textNodes.length;i++) {
        var textNode = textNodes.item(i);
        textNode.setAttributeNS(null,"orig_fill",textNode.getAttributeNS(null,"fill"));
        textNode.setAttributeNS(null,"fill","rgb(0%,0%,100%)");
    }
}

/**
 *  Highlight text (change color back to original color).  Called from onmouseover event.
 */
function unhighlightLink(evt)
{
    var groupNode = evt.currentTarget;
    var textNodes = groupNode.getElementsByTagName("text");

    for (i=0;i<textNodes.length;i++) {
        var textNode = textNodes.item(i);
        var orig_fill = textNode.getAttributeNS(null,"orig_fill");
        if (orig_fill) {
            textNode.setAttributeNS(null,"fill",orig_fill);
        }
    }
}


/*============================================================================
 * General Purpose
 *============================================================================*/
/**
 * Popup in new window
 */
function openLinkInNewWindow(url)
 {
    var svgState = getSvgState();
    if (isAdobeSVGViewer())  {
        browserEval("window.open('" + url + "')");
    } else {
        window.open(url);
    }
 }

function openLinkInWebFrame(url)
 {
    var svgState = getSvgState();
    if (isAdobeSVGViewer())  {
        browserEval("window.openLinkInWebFrame('" + url + "');");
    } else {
        var frameset = top.document.getElementById(gFrameID.frameset_model);
        top.window.frames[gFrameID.web].location.href = url;
        frameset.rows = '0%, 100%';
    }
 }

/**
 *  Find the child node for a given DOM node
 */
function findChildById(thisNode, id)
{
    if (!thisNode) {
        return false;
    }

    var childNode = thisNode.firstChild;
    while (childNode) {
        if (childNode.nodeType == 1) {
            if (childNode.getAttributeNS(null, 'id') == id) {
                return childNode;
            }
        }
        childNode = childNode.nextSibling;
    }
    return false;
}

/**
 *  Find the child node for a given DOM node, starting with the last node
 */
function findChildByIdReverse(thisNode, id)
{
    if (!thisNode) {
        return false;
    }

    var childNode = thisNode.lastChild;
    while (childNode) {
        if (childNode.nodeType == 1) {
            //element
            if (childNode.getAttributeNS(null,'id') == id) {
                return childNode;
            }
        }
        childNode = childNode.previousSibling;
    }
    return false;
}

/**
 *  Find the sibling node given DOM node
 */
function findSiblingById(thisNode, id)
{
    if (!thisNode) {
        return false;
    }
    return findChildById(thisNode.parentNode, id);
}

/**
 *  Find the sibling node given DOM node, starting with the last node
 */
function findSiblingByIdReverse(thisNode, id)
{
    if (!thisNode) {
        return false;
    }
    return findChildByIdReverse(thisNode.parentNode, id);
}

/**
 *  Finds the scrim for the given canvas <svg> element.  Creates one if
 *  necessary.
 *
 *  Note that this does not add the scrim as the node's child.  That is the
 *  responsibility of the caller.
 *
 *  To find the scrim for the current canvas:
 *  var svgState = getSvgState();
 *  var scrim = findScrimElement(svgState.currSysCanvas, svgState.currSys);
 */
function findScrimElement(currCanvas, id)
{
    // scrim is usually the last element
    var scrim = findChildByIdReverse(currCanvas, 'scrim.' + id);
    if (!scrim && currCanvas) {
        var svgState = getSvgState();
        scrim = currCanvas.ownerDocument.createElementNS(gSVGNS, 'rect');
        scrim.setAttributeNS(null, 'id', 'scrim.' + id);
    }
    return scrim;
}

/**
 *  Find zoom box and cache it in a global variable
 */
 /*
var gZoomBox = null;
function findZoomBox()
{
    if (!gZoomBox)
    {
        var svgState = getSvgState();
        gZoomBox = svgState.svgDoc.getElementById('rect.zoomBox');
    }

    return gZoomBox;
}
*/

/**
 *  Find canvas node for a given id
 */
function findCanvasById(id)
{
    var svgState = getSvgState();
    return findChildById(svgState.canvasGroup, 'canvas.' + id);
}

/**
 *  Find all canvases
 */
function findCanvasAll()
{
    var svgState = getSvgState();
    return svgState.canvasGroup.getElementsByTagName('svg');
}

/**
 *  Used to escape out double quotes to form a proper string.  Used when we
 *  define some javascript code in a DOM attribute.
 */
function escapeCharacters(str)
{
    var escapedStr = str.replace(/\\/g,'\\\\');
    escapedStr = escapedStr.replace(/\"/g,'\\"')
    return escapedStr;
}

/**
 *  Get the visible viewbox for a given canvas
 */
function getVisibleViewBox(thisCanvas, thisViewBox)
{
    if (!thisCanvas) {
        var svgState = getSvgState();
        thisCanvas = svgState.currSysCanvas;
    }

    if (!thisViewBox) {
        thisViewBox = thisCanvas.getAttributeNS(null, 'viewBox');
    }

    var vbArray = new Array();
    vbArray = thisViewBox.split(' ');
    vbArray[3] = parseFloat(vbArray[3]); //height
    vbArray[2] = parseFloat(vbArray[2]); //width
    vbArray[1] = parseFloat(vbArray[1]); //top edge
    vbArray[0] = parseFloat(vbArray[0]); //left edge

    var canvasWidth = thisCanvas.getAttributeNS(null, 'width');
    var canvasHeight = thisCanvas.getAttributeNS(null, 'height');
    var winDims = getBrowserInnerWindowDimensions();
    var winWidth = winDims[0];
    var winHeight = winDims[1];

    // Adjust viewbox to get actual viewable area
    if (canvasWidth.indexOf('%') != -1) {
        // Viewbox is specified in percentages.  There is some extra room in
        // the direction unconstrained by aspect ratio.  We can increase the
        // actual vbArray [2] or [3] to compensate
        var winAspectRatio = winHeight/winWidth;
        if (winAspectRatio > vbArray[3]/vbArray[2]) {
            //width-constrained, increase vbHeight
            vbArray[3] = winAspectRatio*vbArray[2];
        } else {
            //height-constrained, increase vbWidth
            vbArray[2] = vbArray[3]/winAspectRatio;
        }

    } else {
        // Fixed scaling.  The viewbox always runs an extra gZN_PAD pixels
        // Adjust to get the actual visible size
        canvasWidth = parseFloat(canvasWidth);
        canvasHeight = parseFloat(canvasHeight);
        vbArray[2] = vbArray[2]*winWidth/canvasWidth;
        vbArray[3] = vbArray[3]*winHeight/canvasHeight;
    }

    return vbArray;
}

/**
 *  Get local coordinates for a given scene coordinates
 */
function getLocalCoords(x, y, viewbox)
{
    if (!viewbox) {
        viewbox = getVisibleViewBox();
    }
    var winDims = getBrowserInnerWindowDimensions();
    var canvasXScale = winDims[0]/viewbox[2];
    var canvasYScale = winDims[1]/viewbox[3];
    var localCoords = new Array();
    localCoords[0] = x/canvasXScale + viewbox[0];
    localCoords[1] = (y - gNavToolbarHeight)/canvasYScale + viewbox[1];

    return localCoords;
}

/*============================================================================
 * Environment tests
 *============================================================================*/

/**
 *  Checks if we are running ASV.  This test must run in the SVG context.
 */
function isAdobeSVGViewer()
{
    var appName = navigator.appName.toLowerCase();
    return (appName.indexOf('adobe svg viewer') != -1);
}

/**
 *  Get browser language.  Should NOT be executed from Adobe SVG plugin context
 */
function getBrowserLanguage()
{
    var lang;

    /*
    if (isAdobeSVGViewer()) {
        alert("getBrowserLanguage() should not be called from Adobe plugin!");

        // Does NOT WORK all the time!
        browserEval('top._slwebview_lang = navigator.browserLanguage');
        if (top._slwebview_lang) {
            lang = top._slwebview_lang;
        } else {
            // alert("Unable to detect browser language");
            lang = "en-US";
        }
        return lang.toLowerCase();
    }
    */

    if (typeof navigator.language == "string") {
        lang = navigator.language; // Mozilla, Netscape
    } else if (typeof navigator.browserLanguage == "string") {
        lang = navigator.browserLanguage; //IE
    } else if (typeof navigator.systemLanguage == "string") {
        lang = navigator.systemLanguage; //IE
    } else if (typeof navigator.userLanguage == "string") {
        lang = navigator.userLanguage; //IE
    } else {
        lang = "en-US"; //default to english
    }

    return lang.toLowerCase();
}

/**
 *  Determines the dimensions of the browser window viewport including.
 *  Calculation includes scollbars.
 */
var gNavToolbarHeight = 30; // Height of the svg navigation toolbar
function getBrowserInnerWindowDimensions()
{
    var dim = new Array();
    var wWidth  = parseFloat(window.innerWidth);
    var wHeight = parseFloat(window.innerHeight) - gNavToolbarHeight;

    // IE does not have window.inner* props.  Use document.body.client* props.
    if (isNaN(wHeight)) {
        wHeight = parseFloat(document.body.clientHeight);
        wWidth = parseFloat(document.body.clientWidth - gNavToolbarHeight);
    }
    dim[0] = wWidth;
    dim[1] = wHeight;

    return dim;
}

/*============================================================================
 * Test Code
 *============================================================================*/
/**
 *  Puts a box at a position
 */
function testRectBox(thisCanvas, x, y)
{
    var rectNode = thisCanvas.ownerDocument.createElement(gSVGNS,'rect');

    rectNode.setAttributeNS(null, 'x', x);
    rectNode.setAttributeNS(null, 'y', y);
    rectNode.setAttributeNS(null, 'width', 10);
    rectNode.setAttributeNS(null, 'height', 10);
    thisCanvas.appendChild(rectNode);
}
