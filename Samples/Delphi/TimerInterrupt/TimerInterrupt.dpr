program TimerInterrupt;

uses
  Vcl.Forms,
  TimerInterruptUnit in 'TimerInterruptUnit.pas' {SampleForm},
  PCI1500 in '..\PCI1500.PAS';

{$R *.res}

begin
  Application.Initialize;
  Application.MainFormOnTaskbar := True;
  Application.CreateForm(TSampleForm, SampleForm);
  Application.Run;
end.
