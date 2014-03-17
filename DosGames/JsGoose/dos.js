var DOS = {
  open : function ( nameaddr )
  {
    var id = this._getStringAt(nameaddr);
    var res64 = getResource(id);
    console.log("Open file '"+id+"' : " + typeof(res64));
    if ( typeof(res64) == "undefined")
      return 0;

    this._filedata = window.atob(res64);
    return 0x1234;
  },
  read : function ( handle, ptr, len )
  {
    var raw = this._filedata;
    var rawLength = raw.length;
    var i;
    for(i = 0; i < rawLength; i++)
      _data[ptr+i] = raw.charCodeAt(i);

    return 0;
  },
  close : function ( handle )
  {
    this._filedata = null;
    return 0;
  },

  _getStringAt : function (addr)
  {
    var name = "";
    for (var i=addr; _data[addr] != 0 && name.length < 128; addr++)
      name += String.fromCharCode(_data[addr]);
    return name;
  },
  _filedata : null

};
