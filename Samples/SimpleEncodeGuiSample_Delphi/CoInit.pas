unit CoInit;

interface

uses ActiveX;

implementation

initialization CoInitializeEx(0, COINIT_MULTITHREADED);

finalization CoUnInitialize;

end.
