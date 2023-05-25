# run this in admin powershell
mkdir ../r24avd1-test
New-Item -ItemType SymbolicLink -Path "../r24avd1-test/esphome-external.yaml" -Target ".\esphome-web-ac358c-external.yaml"
