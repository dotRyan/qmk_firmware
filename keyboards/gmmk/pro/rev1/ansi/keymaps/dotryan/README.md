qmk compile -kb gmmk/pro -km dotryan

added submodule for socd cleaner 
https://getreuer.info/posts/keyboards/socd-cleaner/
```
cd /path/to/qmk_firmware
mkdir -p modules
git submodule add https://github.com/getreuer/qmk-modules.git modules/getreuer
git submodule update --init --recursive
```