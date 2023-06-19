# run this in admin powershell
mkdir ../r24avd1-test
New-Item -ItemType SymbolicLink -Path "../r24avd1-test/esphome-external.yaml" -Target ".\esphome-web-ac358c-external.yaml"
New-Item -ItemType SymbolicLink -Path "../r24avd1-test/esphome-external-balcony.yaml" -Target ".\esphome-web-abf2ec-external.yaml"
New-Item -ItemType SymbolicLink -Path "../r24avd1-test/esphome-external-downstairs.yaml" -Target ".\esphome-web-abf408-external.yaml"
New-Item -ItemType SymbolicLink -Path "../r24avd1-test/esphome-external-lounge.yaml" -Target ".\esphome-web-998ec8.yaml"
