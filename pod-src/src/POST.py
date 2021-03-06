import os

SENSOR_LIST_NAME = "pressure.cpp"
WARNING = "/******** AUTOGENERATED ********/\n\n"


def find_init(filename):
    sensors = []
    init = -1
    with open(filename, "r") as f:
        sensors = f.readlines()
        for line in sensors:
            if line.find("int init") != -1:
                init = line.replace("int", "").replace("{","").replace("\n","").strip(" ")
                break
    return init

def gen_include(name, funcs):
    string = WARNING
    string = string + "#ifndef __BLOOP{}_H__\n".format(name.upper())
    string = string + "#define __BLOOP{}_H__\n".format(name.upper())
    for func in funcs:
        string = string + func + ";\n"

    string = string + "#endif\n"
    write_file("../include/post.h", string)
    return

def gen_post(sensors):
    return 

def gen_init(init): 
    string = """
    if (!{0})
        printf("{0} : SUCCESS\\n\\r");
    else 
        printf("[WARN] {0} Failed to initialize\\n\\r");
""".format(init)
    return string

def add_include(base, name):
    base = base + "#include \"{}\"\n".format(name)
    return base

def write_file(name, content):
    with open(name, "w") as f:
        f.write(content)

if __name__ == "__main__":
    files = os.listdir()
    inits = []
    builder = WARNING
    builder = add_include(builder, "mbed.h")
    builder = add_include(builder, "post.h")
    for f in files:
        if f == "POST.cpp":
            continue
        if f.find(".cpp") != -1:    
            init = find_init(f)
            if init != -1:
                builder = add_include(builder, f.replace("cpp", "h"))
                inits.append(init)

    builder = builder + "void Post() {\n"
    builder = builder + "printf(\"========= Badgerloop Mbed Initilization Sequence =========\\n\\r\");\n"
    for init in inits:
        builder = builder + gen_init(init)
    builder = builder + "printf(\"========= Badgerloop Mbed Initilization Complete =========\\n\\r\");\n"
    builder = builder + "\n}\n"
    write_file("POST.cpp", builder)
    gen_include("post", ["void Post()"])
