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


;; office (ac358c)
(overseer.register_template 
  {:name "esphome run radar OFFICE"
   :builder (fn [params] 
              {:cmd ["esphome"]
               :args ["run" "--device" "esphome-web-ac358c.local"  "esphome-web-ac358c.yaml"]
               :name "esphome run radar OFFICE"
               :env {}
               :cwd (vim.fn.expand "%:h")})})

(overseer.register_template 
  {:name "esphome compile --only-generate radar OFFICE"
   :builder (fn [params] 
              {:cmd ["esphome"]
               :args ["compile" "--only-generate" "esphome-web-ac358c.yaml"]
               :name "esphome compile --only-generate radar OFFICE"
               :env {}
               :cwd (vim.fn.expand "%:h")})})

(overseer.register_template 
  {:name "esphome compile radar OFFICE"
   :builder (fn [params] 
              {:cmd ["esphome"]
               :args ["compile" "esphome-web-ac358c.yaml"]
               :name "esphome compile radar OFFICE"
               :env {}
               :cwd (vim.fn.expand "%:h")})})

(overseer.register_template 
  {:name "esphome clean radar OFFICE"
   :builder (fn [params] 
              {:cmd ["esphome"]
               :args ["clean" "esphome-web-ac358c.yaml"]
               :name "esphome clean radar OFFICE"
               :env {}
               :cwd (vim.fn.expand "%:h")})})


(overseer.register_template 
  {:name "esphome log radar OFFICE"
   :builder (fn [params] 
              {:cmd ["esphome"]
               :args ["logs" "esphome-web-ac358c.yaml" "--client-id" "esphome-web-ac358c.local"]
               :name "esphome clean radar OFFICE"
               :env {}
               :cwd (vim.fn.expand "%:h")
               })})

;; --- external, office (ac358c)
(overseer.register_template 
  {:name "esphome run radar external OFFICE"
   :builder (fn [params] 
              {:cmd ["esphome"]
               :args ["run" "-v" "--device" "esphome-external.yaml"]
               :name "esphome run radar external OFFICE"
               :env {}
               :cwd (.. (vim.fn.expand "%:h") "/../r24avd1-test")})})

(overseer.register_template 
  {:name "esphome clean external OFFICE"
   :builder (fn [params] 
              {:cmd ["esphome"]
               :args ["clean" "esphome-external.yaml"]
               :name "esphome clean radar external OFFICE"
               :env {}
               :cwd (.. (vim.fn.expand "%:h") "/../r24avd1-test")})})

(overseer.register_template 
  {:name "esphome compile radar external OFFICE"
   :builder (fn [params] 
              {:cmd ["esphome"]
               :args ["compile" "esphome-external.yaml"]
               :name "esphome compile radar OFFICE"
               :env {}
               :cwd (.. (vim.fn.expand "%:h") "/../r24avd1-test")})})


;; --- external, balcony (abf2ec)
(overseer.register_template 
  {:name "esphome run radar external BALCONY"
   :builder (fn [params] 
              {:cmd ["esphome"]
               :args ["run" "--device" "esphome-web-radar-1.local"  "esphome-external-balcony.yaml"]
               :name "esphome run radar external BALCONY"
               :env {}
               :cwd (.. (vim.fn.expand "%:h") "/../r24avd1-test")})})

(overseer.register_template 
    {:name "esphome log radar BALCONY"
     :builder (fn [params] 
                {:cmd ["esphome"]
                 :args ["logs" "esphome-external-balcony.yaml" "--client-id" "esphome-web-radar-1.local"]
                 :name "esphome clean radar BALCONY"
                 :env {}
                 :cwd (.. (vim.fn.expand "%:h") "/../r24avd1-test")
                 ; :strategy {1 :jobstart :use_terminal false}
                 })})


;; -- external, downstairs (abf408)

(do

  (defn register-esphome-templates [name client-id device yaml-path cwd] 
    (let [cmd ["esphome"]
          name-prefix "esphome: "
          get-name-fn (fn [cmd device-2] 
                        (.. name-prefix 
                            name " " cmd 
                            (or (and device-2 
                                     (.. " " device-2))
                                "")))
          ]

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

      ;; clean 
      (overseer.register_template 
        {:name (get-name-fn :clean)
         :builder (fn [params] 
                    {:cmd ["esphome"]
                     :args [:clean yaml-path]
                     :name (get-name-fn :clean)
                     :env {}
                     :cwd cwd})})))

  (register-esphome-templates "Entrance"
                              "esphome-abf408-entrance-1.local" 
                              "COM3"
                              "../r24avd1/esphome-abf408-entrance-1.yaml"
                              (.. (vim.fn.expand "%:h") "/../r24avd1-test"))
  )

(overseer.register_template 
    {:name "esphome log radar COM ENTRANCE"
     :builder (fn [params] 
                {:cmd ["esphome"]
                 :args ["logs" "../r24avd1/esphome-abf408-entrance-1.yaml" "--client-id" "esphome-abf408-entrance-1.local"]
                 :name "esphome clean radar ENTRANCE"
                 :env {}
                 :cwd (.. (vim.fn.expand "%:h") "/../r24avd1-test")
                 ; :strategy {1 :jobstart :use_terminal false}
                 })})


(overseer.register_template 
  {:name "esphome compile --only-generate radar OFFICE"
   :builder (fn [params] 
              {:cmd ["esphome"]
               :args ["compile" "--only-generate" "esphome-web-ac358c.yaml"]
               :name "esphome compile --only-generate radar OFFICE"
               :env {}
               :cwd (vim.fn.expand "%:h")})})


(comment

  ;; --- lounge (998ec8)
  (overseer.register_template 
    {:name "esphome run radar LOUNGE"
     :builder (fn [params] 
                {:cmd ["esphome"]
                 :args ["run" "--device" "COM3" "esphome-external-lounge.yaml" ]
                 :name "esphome run radar LOUNGE"
                 :env {}
                 :cwd (.. (vim.fn.expand "%:h") "/../r24avd1-test")
                 })})

  (overseer.register_template 
    {:name "esphome upload radar LOUNGE"
     :builder (fn [params] 
                {:cmd ["esphome"]
                 :args ["upload" "--device" "COM3" "esphome-external-lounge.yaml" ]
                 :name "esphome upload radar LOUNGE"
                 :env {}
                 :cwd (.. (vim.fn.expand "%:h") "/../r24avd1-test")
                 })})

  (overseer.register_template 
    {:name "esphome compile radar LOUNGE"
     :builder (fn [params] 
                {:cmd ["esphome"]
                 :args ["compile" "--only-generate" "esphome-web-998ec8.yaml"]
                 :name "esphome compile radar LOUNGE"
                 :env {}
                 :cwd (vim.fn.expand "%:h")
                 ; :strategy {1 :jobstart :use_terminal false}
                 })})

  (overseer.register_template 
    {:name "esphome clean radar LOUNGE"
     :builder (fn [params] 
                {:cmd ["esphome"]
                 :args ["clean" "esphome-web-998ec8.yaml"]
                 :name "esphome clean radar"
                 :env {}
                 :cwd (vim.fn.expand "%:h")
                 ; :strategy {1 :jobstart :use_terminal false}
                 })})

  (overseer.register_template 
    {:name "esphome log radar LOUNGE"
     :builder (fn [params] 
                {:cmd ["esphome"]
                 :args ["logs" "esphome-web-998ec8.yaml" "--client-id" "esphome-web-998ec8.local"]
                 :name "esphome clean radar LOUNGE"
                 :env {}
                 :cwd (vim.fn.expand "%:h")
                 ; :strategy {1 :jobstart :use_terminal false}
                 })})
  )
