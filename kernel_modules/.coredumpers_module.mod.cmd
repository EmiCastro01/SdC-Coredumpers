savedcmd_coredumpers_module.mod := printf '%s\n'   coredumpers_module.o | awk '!x[$$0]++ { print("./"$$0) }' > coredumpers_module.mod
