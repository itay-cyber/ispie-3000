# script to generate model class boilerplate ;(

import os

NEW_MODULE_BASE_PATH = "app/modules/{}"
TEMPLATE_MODULE_CNAME = "TemplateModule"
TEMPLATE_MODULE_CONST_NAME = "TEMPLATE_MODULE_NAME"
TEMPLATE_MODULE_LOC = "core/template"
APP_DEFS_FILE_LOC = "app/definitions.h"

TEMPLATE_MODULE_DEFS_FILE_NAME = f"""        const std::string {TEMPLATE_MODULE_CONST_NAME} = "{TEMPLATE_MODULE_CNAME}";\n"""


def get_module_name() -> str:
    module_name = input("Enter new module name (e.g 'ShoMe', 'Tutor', 'ScanMe'): ")
    if module_name == "":
        raise TypeError("Invalid module name")
    
    return module_name

def get_template_file_header(module_name: str) -> str:
    template_module_header: str = ""
    with open(f"{TEMPLATE_MODULE_LOC}/template_module.h", "r+") as header_file:
        template_module_header = header_file.read()
        template_module_header = template_module_header.replace(TEMPLATE_MODULE_CNAME, f"{module_name}Module")
        template_module_header = template_module_header.replace(TEMPLATE_MODULE_CONST_NAME, f"{module_name.upper()}_MODULE_NAME")
    
    return template_module_header
    
def get_template_file_source(module_name: str) -> str:
    template_module_source: str = ""
    with open(f"{TEMPLATE_MODULE_LOC}/template_module.cpp", "r+") as header_file:
        template_module_source = header_file.read()
        template_module_source = template_module_source.replace(TEMPLATE_MODULE_CNAME, f"{module_name}Module")
        template_module_source = template_module_source \
            .replace(f"{TEMPLATE_MODULE_LOC}/template_module.h", f"{NEW_MODULE_BASE_PATH.format(module_name.lower())}/{module_name.lower()}_module.h")

    return template_module_source

def update_defs_file(module_name: str):
    defs_file_contents: list[str]
    new_module_const_str = TEMPLATE_MODULE_DEFS_FILE_NAME.replace(TEMPLATE_MODULE_CONST_NAME, f"{module_name.upper()}_MODULE_NAME").replace(TEMPLATE_MODULE_CNAME, f"{module_name}Module")
    with open(APP_DEFS_FILE_LOC, "r+") as defs_file:
        defs_file_contents = defs_file.readlines()
        sqr_close = -1
        for (num, line) in enumerate(defs_file_contents):
            if '}' in line:
                sqr_close = num
                break
        
        if sqr_close != -1:
            defs_file_contents.insert(num, new_module_const_str)
    with open(APP_DEFS_FILE_LOC, "w+") as defs_file:
        defs_file.writelines(defs_file_contents)

def main():
    # get module name from user
    module_name = get_module_name()
    template_module_header_str = get_template_file_header(module_name)
    template_module_source_str = get_template_file_source(module_name)

    base_path = NEW_MODULE_BASE_PATH.format(module_name.lower())
    if os.path.exists(base_path):
        raise(FileExistsError, "Module already exists. Enter a different name")
    os.mkdir(base_path)
    with open(f"{base_path}/{module_name.lower()}_module.h", 'x') as new_header_file, \
         open(f"{base_path}/{module_name.lower()}_module.cpp", 'x') as new_source_file:
        new_header_file.write(template_module_header_str)
        new_source_file.write(template_module_source_str)

    update_defs_file(module_name)
    print(f"Generated new {module_name}Module, at {os.path.abspath(base_path)}")
    
        
if __name__ == "__main__":
    main()
