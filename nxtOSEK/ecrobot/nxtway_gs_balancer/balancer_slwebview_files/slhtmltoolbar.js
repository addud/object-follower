/**
 *  JavaScript library for the Simulink Web View's EML Toolbars
 * 
 *  Copyright 1997-2008 The MathWorks, Inc.
 */

function toolbarButton(imgLoc, tooltipText, onClickAction, mouseOverAction, mouseOutAction)
{
    this.image = document.createElement("img");
    this.image.src = imgLoc;
    this.image.tooltipText = tooltipText;
    this.image.className = "toolbarButton";
    
    addEventListener(this.image, "mouseover", (mouseOverAction == null || mouseOverAction == undefined ? onMouseOverButton : mouseOverAction));
    addEventListener(this.image, "mouseleave", (mouseOutAction == null || mouseOutAction == undefined ? onMouseOutOfButton : mouseOutAction));
    addEventListener(this.image, "mouseout", (mouseOutAction == null || mouseOutAction == undefined ? onMouseOutOfButton : mouseOutAction));    
    
    if(onClickAction != null && onClickAction != undefined)
    {
        addEventListener(this.image, "click", onClickAction);
    }
}

function addToolbar(domContainerName, recurseCount)
{
    var buttons = new Array();
    
    buttons.push( new toolbarButton('buttons/helpButton.png',    "",                  null,             showNavigationDropDown));
    buttons.push( new toolbarButton('buttons/upButton.png',      "View Home",         changeSysHome));
    buttons.push( new toolbarButton('buttons/prevButton.png',    "View Previous",     changeSysPrev));
    buttons.push( new toolbarButton('buttons/showAllButton.png', "Show all layers",   toggleExpose));
    
    //    If the page has finished loading, append to the existing object
    if(document.body != null)
    {
        var domContainer = document.getElementById(domContainerName);
        
        for(var i = 0; domContainer != null && i < buttons.length; i++)
        {
            domContainer.appendChild(buttons[i].image);
        }
    }
    //    Otherwise, wait for the load to complete and try again (for up to 10 seconds)
    else if(recurseCount < 100)
    {
        if(recurseCount == undefined)
        {
            recurseCount = 0;
        }
            
        setTimeout('addToolbar("' + domContainerName + '",' + (recurseCount + 1) + ');', 100);
    }
}
g__NAV_DROP_DOWN = null;
function onMouseOutOfNavDropdown(evt)
{
    evt = getEvent(evt);
    
    var sourceElement = evt.relatedTarget || evt.toElement;

    //    If the element under the mouse is not a child of the nav dropdown, hide the nav
    if(!isChildElement(sourceElement, this))
    {
        hideNavigationDropDown();
    }
}
function hideNavigationDropDown()
{
    if(g__NAV_DROP_DOWN != null)
    {
        g__NAV_DROP_DOWN.style.display = "none";
    }
}
function showNavigationDropDown()
{
    if(g__NAV_DROP_DOWN == null)
    {
        g__NAV_DROP_DOWN = createNewToolTip();
        
        addEventListener(g__NAV_DROP_DOWN, "mouseout", onMouseOutOfNavDropdown);
        addEventListener(g__NAV_DROP_DOWN, "mouseleave", onMouseOutOfNavDropdown);
        
        g__NAV_DROP_DOWN.firstChild.innerHTML = "Navigation Commands<br><br>" + 
                                        "<span class='navDropDownItem' onclick='hideNavigationDropDown();toggleExpose();'>&nbsp;&nbsp;X&nbsp;&nbsp;</span>" +
                                        "&nbsp;&nbsp;Show all layers";
    }
    
    g__NAV_DROP_DOWN.style.display = "";
    g__NAV_DROP_DOWN.style.left = getOffsetLeft(this);
    g__NAV_DROP_DOWN.style.top = getOffsetTop(this);
}
function isChildElement(child, parent)
{
    if(child == parent)
    {
        return true;
    }
    
    if(child == undefined || child.parentNode == undefined || child.parentNode == null)
    {
        return false;
    }
    
    if(child.parentNode == parent)
    {
        return true;
    }
        
    return isChildElement(child.parentNode, parent);
}
function onMouseOverButton(evt)
{
    if(this.tooltipText != undefined && this.tooltipText != "")
    {
        showToolTip(this.tooltipText, getOffsetLeft(this) + this.offsetWidth, getOffsetTop(this) + this.offsetHeight);
    }
}
function onMouseOutOfButton()
{
    hideToolTip();
}