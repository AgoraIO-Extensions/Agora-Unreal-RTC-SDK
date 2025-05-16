import argparse
import yaml
from pathlib import Path
import shutil

def replace_in_yaml(file_path, new_version):
    try:
        with open(file_path, 'r', encoding='utf-8') as file:
            content = file.read()

        ## Replace
        new_content = content.replace('{{SDK_VERSION}}', new_version)

        try:
            yaml.safe_load(new_content)
        except yaml.YAMLError as e:
            print(f"Warning: Modified content in {file_path} might not be valid YAML: {str(e)}")
            return False

        with open(file_path, 'w', encoding='utf-8') as file:
            file.write(new_content)
        return True

    except Exception as e:
        print(f"Error processing {file_path}: {str(e)}")
        return False

def main():
    parser = argparse.ArgumentParser(description='Replace {{SDK_VERSION}} in YAML files with specified version')
    parser.add_argument("-agorasdktype", default="rtc")
    parser.add_argument("-agorasdk", default="4.4.0")
    
    args = parser.parse_args()

    str_sdk_ver = f"{args.agorasdktype}_{args.agorasdk}"

    path_config_base = Path("./config")
    path_config_bp_tmpl = path_config_base / "templates" / "blueprint_config_tmpl.yaml"
    path_config_bp = path_config_base / "blueprint_config.yaml"

    path_config_cpp_tmpl = path_config_base  / "templates" / "cpp_config_tmpl.yaml"
    path_config_cpp = path_config_base / "cpp_config.yaml"

    
    if path_config_bp.exists():
        path_config_bp.unlink()
    if path_config_cpp.exists():
        path_config_cpp.unlink()

    shutil.copy2(path_config_bp_tmpl,path_config_bp)
    shutil.copy2(path_config_cpp_tmpl,path_config_cpp)

    replace_in_yaml(path_config_bp,str_sdk_ver)
    replace_in_yaml(path_config_cpp,str_sdk_ver)

    
if __name__ == "__main__":
    main()