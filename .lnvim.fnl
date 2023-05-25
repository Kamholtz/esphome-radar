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




(overseer.register_template {:name "esphome run radar OFFICE"
                             :builder (fn [params] 
                                        {:cmd ["esphome"]
                                         :args ["run" "--device" "esphome-web-ac358c.local"  "esphome-web-ac358c.yaml"]
                                         :name "esphome run radar OFFICE"
                                         :env {}
                                         :cwd (vim.fn.expand "%:h")
                                         ; :strategy {1 :jobstart :use_terminal false}
                                         })})

(overseer.register_template {:name "esphome compile --only-generate radar OFFICE"
                             :builder (fn [params] 
                                        {:cmd ["esphome"]
                                         :args ["compile" "--only-generate" "esphome-web-ac358c.yaml"]
                                         :name "esphome compile --only-generate radar OFFICE"
                                         :env {}
                                         :cwd (vim.fn.expand "%:h")
                                         ; :strategy {1 :jobstart :use_terminal false}
                                         })})

(overseer.register_template {:name "esphome compile radar OFFICE"
                             :builder (fn [params] 
                                        {:cmd ["esphome"]
                                         :args ["compile" "esphome-web-ac358c.yaml"]
                                         :name "esphome compile radar OFFICE"
                                         :env {}
                                         :cwd (vim.fn.expand "%:h")
                                         ; :strategy {1 :jobstart :use_terminal false}
                                         })})


(overseer.register_template {:name "esphome run radar test OFFICE"
                             :builder (fn [params] 
                                        {:cmd ["esphome"]
                                         :args ["run" "--device" "esphome-web-ac358c.local"  "esphome-test.yaml"]
                                         :name "esphome run radar test OFFICE"
                                         :env {}
                                         :cwd (.. (vim.fn.expand "%:h") "/../r24avd1-test")
                                         ; :strategy {1 :jobstart :use_terminal false}
                                         })})

(overseer.register_template {:name "esphome compile radar test OFFICE"
                             :builder (fn [params] 
                                        {:cmd ["esphome"]
                                         :args ["compile" "esphome-test.yaml"]
                                         :name "esphome compile radar OFFICE"
                                         :env {}
                                         :cwd (.. (vim.fn.expand "%:h") "/../r24avd1-test")
                                         ; :strategy {1 :jobstart :use_terminal false}
                                         })})

(overseer.register_template {:name "esphome clean radar OFFICE"
                             :builder (fn [params] 
                                        {:cmd ["esphome"]
                                         :args ["clean" "esphome-web-ac358c.yaml"]
                                         :name "esphome clean radar OFFICE"
                                         :env {}
                                         :cwd (vim.fn.expand "%:h")
                                         ; :strategy {1 :jobstart :use_terminal false}
                                         })})

(overseer.register_template {:name "esphome log radar OFFICE"
                             :builder (fn [params] 
                                        {:cmd ["esphome"]
                                         :args ["logs" "esphome-web-ac358c.yaml" "--client-id" "esphome-web-ac358c.local"]
                                         :name "esphome clean radar OFFICE"
                                         :env {}
                                         :cwd (vim.fn.expand "%:h")
                                         ; :strategy {1 :jobstart :use_terminal false}
                                         })})



(comment

 (overseer.register_template {:name "esphome run radar LOUNGE"
                              :builder (fn [params] 
                                         {:cmd ["esphome"]
                                          :args ["run" "--device" "esphome-web-998ec8.local"  "esphome-web-998ec8.yaml"]
                                          :name "esphome run radar LOUNGE"
                                          :env {}
                                          :cwd (vim.fn.expand "%:h")
                                          ; :strategy {1 :jobstart :use_terminal false}
                                          })})

 (overseer.register_template {:name "esphome compile radar LOUNGE"
                              :builder (fn [params] 
                                         {:cmd ["esphome"]
                                          :args ["compile" "--only-generate" "esphome-web-998ec8.yaml"]
                                          :name "esphome compile radar LOUNGE"
                                          :env {}
                                          :cwd (vim.fn.expand "%:h")
                                          ; :strategy {1 :jobstart :use_terminal false}
                                          })})

 (overseer.register_template {:name "esphome clean radar LOUNGE"
                              :builder (fn [params] 
                                         {:cmd ["esphome"]
                                          :args ["clean" "esphome-web-998ec8.yaml"]
                                          :name "esphome clean radar"
                                          :env {}
                                          :cwd (vim.fn.expand "%:h")
                                          ; :strategy {1 :jobstart :use_terminal false}
                                          })})

 (overseer.register_template {:name "esphome log radar LOUNGE"
                              :builder (fn [params] 
                                         {:cmd ["esphome"]
                                          :args ["logs" "esphome-web-998ec8.yaml" "--client-id" "esphome-web-998ec8.local"]
                                          :name "esphome clean radar LOUNGE"
                                          :env {}
                                          :cwd (vim.fn.expand "%:h")
                                          ; :strategy {1 :jobstart :use_terminal false}
                                          })})
 )
