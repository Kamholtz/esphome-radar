(local a (require :nvim-local-fennel.aniseed.core))
(local str (require :nvim-local-fennel.aniseed.string))
(local nvim (require :nvim-local-fennel.aniseed.nvim))
(local fs (require :aniseed.fs))
(local scandir (require :plenary.scandir))
(local path (require :plenary.path))
(local overseer (require :overseer))
(local config-fs (require :config.fs))
(local config-overseer (require :config.plugin.overseer))
(local esphome (require :config.esphome))

(local this-path (vim.fn.expand "%:h"))

(comment
 ;; --- external, downstairs (abf408)
 (esphome.register-esphome-templates "Entrance"
                                     "192.168.2.197" 
                                     ; "esphome-abf408-entrance-1.local" 
                                     "COM3"
                                     "../r24avd1/esphome-abf408-entrance-1.yaml"
                                     (.. this-path "/../r24avd1-test"))

 ;; --- external, office (ac358c)
 (esphome.register-esphome-templates "External Office"
                                     "esphome-web-ac358c.local" 
                                     "COM3"
                                     "esphome-external-lounge.yaml"
                                     (.. this-path "/../r24avd1-test"))

 ;; --- lounge (998ec8)
 (esphome.register-esphome-templates "Lounge"
                                     "esphome-web-998ec8.local" 
                                     "COM3"
                                     "../r24avd1/esphome-web-998ec8.yaml"
                                     (.. this-path "/../r24avd1-test"))
 )

(esphome.register-esphome-templates "Office R24"
                                    "office-r24.local" 
                                    "COM3"
                                    "../r24avd1/office-r24.yaml"
                                    (.. this-path "/../r24avd1-test"))

;; --- external, office (ac358c)
;; Not in use
;; --- external, balcony (abf2ec)
;; Not in use

