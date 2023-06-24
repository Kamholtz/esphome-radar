(module overseer-commands
  {autoload {a nvim-local-fennel.aniseed.core
             str nvim-local-fennel.aniseed.string
             nvim nvim-local-fennel.aniseed.nvim
             fs aniseed.fs
             scandir plenary.scandir
             path plenary.path
             overseer overseer
             config-fs config.fs
             config-overseer config.plugin.overseer}})

(do

  (defn register-esphome-templates [name client-id device yaml-path cwd] 
    (let [cmd ["esphome"]
          name-prefix "esphome: "
          get-name-fn (fn [cmd device-2] 
                        (.. name-prefix name " " cmd 
                            (or (and device-2 
                                     (.. " " device-2))
                                "")))]

      ;; --- COM port commands
      (when device 
        (do 
          ;; run (COM)
          (overseer.register_template 
            {:name (get-name-fn :run device)
             :builder (fn [params] 
                        {:cmd ["esphome"]
                         :args ["run" "--device" device yaml-path]
                         :name (get-name-fn :run device)
                         :env {}
                         :cwd cwd})})

          ;; upload (COM)
          (overseer.register_template 
            {:name (get-name-fn :upload device)
             :builder (fn [params] 
                        {:cmd ["esphome"]
                         :args [:upload "--device" device yaml-path]
                         :name (get-name-fn :upload device)
                         :env {}
                         :cwd cwd})})

          ;; logs (COM)
          (overseer.register_template 
            {:name (get-name-fn :logs device)
             :builder (fn [params] 
                        {:cmd ["esphome"]
                         :args [:logs yaml-path "--client-id" device]
                         :name (get-name-fn :logs device)
                         :env {}
                         :cwd cwd})})))


      ;; --- IP commands
      ;; run (IP)
      (overseer.register_template 
        {:name (get-name-fn :run)
         :builder (fn [params] 
                    {:cmd ["esphome"]
                     :args [:run "--device" client-id yaml-path]
                     :name (get-name-fn :run)
                     :env {}
                     :cwd cwd})})

      ;; upload (IP)
      (overseer.register_template 
        {:name (get-name-fn :upload client-id)
         :builder (fn [params] 
                    {:cmd ["esphome"]
                     :args [:upload "--device" client-id yaml-path]
                     :name (get-name-fn :upload client-id)
                     :env {}
                     :cwd cwd})})

      ;; logs (IP)
      (overseer.register_template 
        {:name (get-name-fn :logs)
         :builder (fn [params] 
                    {:cmd ["esphome"]
                     :args [:logs yaml-path "--client-id" client-id]
                     :name (get-name-fn :logs)
                     :env {}
                     :cwd cwd})})

      ;; --- local commands
      ;; compile 
      (overseer.register_template 
        {:name (get-name-fn :compile)
         :builder (fn [params] 
                    {:cmd ["esphome"]
                     :args ["compile" yaml-path]
                     :name (get-name-fn :compile)
                     :env {}
                     :cwd cwd})})

      ;; clean
      (overseer.register_template 
        {:name (get-name-fn :clean)
         :builder (fn [params] 
                    {:cmd ["esphome"]
                     :args [:clean yaml-path]
                     :name (get-name-fn :clean)
                     :env {}
                     :cwd cwd})})))

  ;; --- external, downstairs (abf408)
  (let [this-path (vim.fn.expand "%:h")] 
    (register-esphome-templates "Entrance"
                                "esphome-abf408-entrance-1.local" 
                                "COM3"
                                "../r24avd1/esphome-abf408-entrance-1.yaml"
                                (.. this-path "/../r24avd1-test"))

    ;; --- external, office (ac358c)
    (register-esphome-templates "External Office"
                                "esphome-web-ac358c.local" 
                                "COM3"
                                "esphome-external-lounge.yaml"
                                (.. (vim.fn.expand "%:h") "/../r24avd1-test"))

    ;; --- lounge (998ec8)
    (register-esphome-templates "Lounge"
                                "esphome-web-998ec8.local" 
                                "COM3"
                                "../r24avd1/esphome-web-998ec8.yaml"
                                (.. (vim.fn.expand "%:h") "/../r24avd1-test")))

  ;; --- external, office (ac358c)
  ;; Not in use
  ;; --- external, balcony (abf2ec)
  ;; Not in use
)
