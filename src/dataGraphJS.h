const char JS_GRAPH[] PROGMEM = R"=====(
function lineGraph(parent,xAccessor,yAccessor){const width=620;const height=420;const gutter=40;const pixelsPerTick=30;function numericTransformer(dataMin,dataMax,pxMin,pxMax){var dataDiff=dataMax-dataMin,pxDiff=pxMax-pxMin,dataRatio=pxDiff/dataDiff,coordRatio=dataDiff/pxDiff;return{toCoord:function(data){return(data-dataMin)*dataRatio+pxMin;},toData:function(coord){return(coord-pxMin)*coordRatio+dataMin;}};}
function axisRenderer(orientation,transform){var axisGroup=document.createElementNS("http://www.w3.org/2000/svg","g");var axisPath=document.createElementNS("http://www.w3.org/2000/svg","path");axisGroup.setAttribute("class",orientation+"-axis");var xMin=gutter;var xMax=width-gutter;var yMin=height-gutter;var yMax=gutter;if(orientation==="x"){axisPath.setAttribute("d","M "+xMin+" "+yMin+" L "+xMax+" "+yMin);for(var i=xMin;i<=xMax;i++){if((i-xMin)%pixelsPerTick===0&&i!==xMin){var text=document.createElementNS("http://www.w3.org/2000/svg","text");text.innerHTML=Math.floor(transform(i));text.setAttribute("x",i);text.setAttribute("y",yMin);text.setAttribute("dy","1em");axisGroup.appendChild(text);}}}else{axisPath.setAttribute("d","M "+xMin+" "+yMin+" L "+xMin+" "+yMax);for(var i=yMax;i<=yMin;i++){if((i-yMin)%pixelsPerTick===0&&i!==yMin){var tickGroup=document.createElementNS("http://www.w3.org/2000/svg","g");var gridLine=document.createElementNS("http://www.w3.org/2000/svg","path");text=document.createElementNS("http://www.w3.org/2000/svg","text");text.innerHTML=Math.floor(transform(i));text.setAttribute("x",xMin);text.setAttribute("y",i);text.setAttribute("dx","-.5em");text.setAttribute("dy",".3em");gridLine.setAttribute("d","M "+xMin+" "+i+" L "+xMax+" "+i);tickGroup.appendChild(gridLine);tickGroup.appendChild(text);axisGroup.appendChild(tickGroup);}}}
axisGroup.appendChild(axisPath);parent.appendChild(axisGroup);}
function lineRenderer(xAccessor,yAccessor,xTransform,yTransform){var line=document.createElementNS("http://www.w3.org/2000/svg","path");xAccessor.reset();yAccessor.reset();if(!xAccessor.hasNext()||!yAccessor.hasNext()){return;}
var pathString="M "+xTransform(xAccessor.next())+" "+yTransform(yAccessor.next());while(xAccessor.hasNext()&&yAccessor.hasNext()){pathString+=" L "+
xTransform(xAccessor.next())+
" "+
yTransform(yAccessor.next());}
line.setAttribute("class","series");line.setAttribute("d",pathString);parent.appendChild(line);}
function pointRenderer(xAccessor,yAccessor,xTransform,yTransform){var pointGroup=document.createElementNS("http://www.w3.org/2000/svg","g");pointGroup.setAttribute("class","data-points");xAccessor.reset();yAccessor.reset();if(!xAccessor.hasNext()||!yAccessor.hasNext()){return;}
while(xAccessor.hasNext()&&yAccessor.hasNext()){var xDataValue=xAccessor.next();var x=xTransform(xDataValue);var yDataValue=yAccessor.next();var y=yTransform(yDataValue);var circle=document.createElementNS("http://www.w3.org/2000/svg","circle");circle.setAttribute("cx",x);circle.setAttribute("cy",y);circle.setAttribute("r","4");var text=document.createElementNS("http://www.w3.org/2000/svg","text");text.innerHTML=Math.floor(xDataValue)+" / "+Math.floor(yDataValue);text.setAttribute("x",x);text.setAttribute("y",y);text.setAttribute("dx","1em");text.setAttribute("dy","-.7em");pointGroup.appendChild(circle);pointGroup.appendChild(text);}
parent.appendChild(pointGroup);}
xTransform=numericTransformer(xAccessor.min(),xAccessor.max(),0+gutter,width-gutter);yTransform=numericTransformer(yAccessor.min(),yAccessor.max(),height-gutter,0+gutter);axisRenderer("x",xTransform.toData);axisRenderer("y",yTransform.toData);lineRenderer(xAccessor,yAccessor,xTransform.toCoord,yTransform.toCoord);pointRenderer(xAccessor,yAccessor,xTransform.toCoord,yTransform.toCoord);}
function renderGraphSvg(dataArray,renderId){var figure=document.getElementById(renderId);while(figure.hasChildNodes()){figure.removeChild(figure.lastChild);}
var svg=document.createElementNS("http://www.w3.org/2000/svg","svg");svg.setAttribute("viewBox","0 0 640 440");svg.setAttribute("preserveAspectRatio","xMidYMid meet");lineGraph(svg,(function(data,min,max){var i=0;return{hasNext:function(){return i<data.length;},next:function(){return data[i++].x;},reset:function(){i=0;},min:function(){return min;},max:function(){return max;}};})(dataArray,Math.min.apply(Math,dataArray.map(function(o){return o.x;})),Math.max.apply(Math,dataArray.map(function(o){return o.x;}))),(function(data,min,max){var i=0;return{hasNext:function(){return i<data.length;},next:function(){return data[i++].y;},reset:function(){i=0;},min:function(){return min;},max:function(){return max;}};})(dataArray,Math.min.apply(Math,dataArray.map(function(o){return o.y;})),Math.max.apply(Math,dataArray.map(function(o){return o.y;}))));figure.appendChild(svg);}
)=====";

const uint8_t JS_GRAPH_GZIP[1245] PROGMEM = { 31,139,8,0,124,57,147,98,2,255,205,87,95,111,219,54,16,127,247,167,112,4,44,16,107,89,86,27,175,3,170,240,33,109,135,174,64,18,20,77,48,96,24,246,192,73,180,76,76,150,4,138,182,69,184,254,238,59,146,162,36,219,82,134,58,45,186,135,56,226,253,231,241,119,119,228,98,157,69,130,229,217,56,101,25,253,192,73,177,116,11,194,105,38,188,234,38,138,104,89,230,220,147,246,11,237,162,60,43,197,120,203,98,177,196,175,95,5,161,89,47,41,75,150,2,207,27,66,178,22,130,114,60,183,235,130,85,52,45,63,81,254,200,162,127,240,85,16,46,172,219,108,189,162,156,69,143,156,100,229,34,231,176,112,99,34,200,29,203,60,253,159,84,94,81,169,21,252,146,10,237,54,132,143,21,227,61,91,44,112,45,49,181,26,69,165,201,90,116,106,212,20,235,51,1,87,216,48,103,86,217,139,242,156,199,134,101,105,51,35,19,114,42,214,60,219,137,252,157,146,121,99,131,213,145,161,157,225,234,133,245,140,94,52,126,38,218,111,184,247,68,254,30,104,173,178,246,215,104,235,149,137,17,189,104,67,153,212,6,195,253,62,220,143,154,44,145,138,149,159,105,22,83,14,249,201,57,131,243,81,210,153,39,108,222,76,102,148,220,7,158,175,11,28,231,17,100,54,19,126,196,41,17,244,215,148,170,213,253,131,235,44,133,40,222,204,102,219,237,214,223,94,249,57,79,102,175,130,32,152,149,155,196,241,156,196,65,161,53,244,137,192,33,159,105,167,0,93,48,213,196,227,151,84,220,8,193,217,223,107,65,93,39,74,73,89,58,94,103,39,19,103,170,132,107,247,42,45,216,128,168,94,147,10,107,212,77,59,84,169,164,12,246,14,201,32,92,175,217,162,155,46,140,177,83,57,104,103,119,119,20,85,12,129,223,141,157,137,242,62,113,224,67,154,143,91,77,35,85,67,67,33,164,220,85,190,24,214,167,205,174,177,18,8,217,100,130,118,224,211,101,83,125,178,63,29,2,31,227,224,242,146,93,96,173,100,78,76,208,74,156,155,100,165,11,9,83,255,124,150,101,148,255,246,120,119,139,239,212,198,22,41,64,202,109,208,225,50,84,203,29,238,184,114,60,214,203,144,142,103,54,218,195,139,129,233,188,164,171,131,243,37,69,1,248,124,183,100,105,236,42,29,4,8,222,195,214,233,121,201,110,104,80,243,157,100,75,157,228,107,44,117,210,219,100,203,167,146,45,219,100,3,253,155,148,71,194,89,124,11,13,243,153,229,241,195,15,191,26,58,99,57,4,140,24,180,156,169,255,179,62,254,33,112,248,87,154,109,179,244,95,39,207,142,107,76,185,182,71,117,128,44,107,113,136,111,144,55,128,74,171,161,161,57,234,23,178,96,69,161,153,130,39,76,107,161,237,205,106,112,54,189,185,103,104,122,85,51,220,60,249,120,216,175,211,231,99,168,241,232,115,10,121,118,81,40,79,40,80,36,23,173,220,146,148,247,144,39,23,125,249,114,33,79,169,118,68,193,30,85,136,202,205,3,156,93,150,96,115,106,205,22,218,205,250,153,209,52,53,219,10,200,99,129,112,11,137,164,110,79,44,151,151,189,161,180,222,39,216,128,100,244,100,0,35,21,193,232,201,16,246,163,244,20,147,245,64,114,74,184,140,80,53,133,210,94,220,182,225,244,2,36,213,208,236,96,163,200,89,38,206,5,135,86,126,118,187,106,173,12,108,89,223,99,180,84,249,157,225,244,181,135,175,39,191,186,68,253,78,210,53,197,199,167,109,110,6,184,139,135,70,216,48,101,171,44,251,148,37,238,34,229,72,57,98,60,74,207,174,78,163,13,9,53,31,199,185,87,189,119,136,167,102,239,0,143,131,229,121,61,131,190,235,240,232,100,18,138,122,6,69,213,97,118,51,53,48,87,6,47,21,195,67,229,229,147,35,101,234,255,162,249,29,56,119,43,207,100,107,144,93,223,72,70,61,53,219,106,40,129,22,76,184,231,101,210,34,112,197,50,23,121,157,53,169,96,29,76,204,181,211,235,94,85,161,130,158,52,42,143,140,202,35,163,7,23,220,198,133,153,114,77,107,209,73,111,172,250,230,237,113,44,163,242,127,42,243,21,243,203,175,95,68,135,102,52,169,78,253,183,48,212,233,159,92,155,211,207,210,135,77,162,159,92,55,156,19,233,25,198,199,216,52,137,5,75,214,188,83,170,9,21,117,37,188,149,31,99,183,17,174,199,143,17,87,157,70,67,224,62,143,105,169,250,77,77,231,116,149,111,168,65,71,77,130,86,41,52,1,213,83,17,202,232,220,218,83,191,40,132,223,35,152,111,24,221,190,205,85,37,4,227,96,252,122,30,140,231,243,160,87,178,80,141,152,111,232,77,89,208,72,232,119,35,104,193,117,42,254,3,254,198,43,74,69,61,193,204,131,30,44,120,238,193,35,214,3,168,121,43,251,158,102,56,176,79,222,186,251,182,175,86,219,190,199,236,90,41,250,41,205,18,177,132,231,109,214,47,166,132,254,132,155,249,95,126,5,66,122,98,116,165,148,171,189,242,222,163,186,210,207,102,136,170,143,7,247,126,245,36,70,29,12,232,142,4,74,170,156,83,233,170,165,215,112,161,120,138,118,207,121,99,40,87,113,33,84,43,147,234,28,101,244,3,178,41,255,167,217,148,207,201,166,86,134,43,89,93,101,221,182,12,152,133,90,251,23,198,24,146,161,158,18,0,0 };
