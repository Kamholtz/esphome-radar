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



(overseer.register_template {:name "esphome run radar"
                             :builder (fn [params] 
                                        {:cmd ["esphome"]
                                         :args ["run" "--device" "esphome-web-ac358c.local"  "esphome-web-ac358c.yaml"]
                                         :name "esphome run radar"
                                         :env {}
                                         ; :strategy {1 :jobstart :use_terminal false}
                                         })})



