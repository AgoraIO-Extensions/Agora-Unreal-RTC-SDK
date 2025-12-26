import os
import shutil
import argparse
import sys

def main():
    parser = argparse.ArgumentParser(description='Update Agora SDK headers')
    parser.add_argument('--source_dir', required=True, help='Path to the source include directory')
    args = parser.parse_args()

    # Paths
    # Script is in .github/ci/
    script_dir = os.path.dirname(os.path.realpath(__file__))
    # Project root is ../../ from .github/ci
    project_root = os.path.realpath(os.path.join(script_dir, '..', '..'))
    
    target_dir = os.path.join(project_root, "Agora-Unreal-SDK-CPP", "AgoraPlugin", "Source", "AgoraPlugin", "Public", "AgoraCppPlugin", "include")
    
    # Verify source directory
    source_include_path = os.path.abspath(args.source_dir)
    if not os.path.exists(source_include_path):
        print(f"Error: Source include directory not found at {source_include_path}")
        sys.exit(1)
            
    try:
        # Clean target directory
        if os.path.exists(target_dir):
            print(f"Cleaning target directory: {target_dir}")
            # Remove all files in target dir
            for item in os.listdir(target_dir):
                item_path = os.path.join(target_dir, item)
                if os.path.isfile(item_path) or os.path.islink(item_path):
                    os.unlink(item_path)
                elif os.path.isdir(item_path):
                    shutil.rmtree(item_path)
        else:
            os.makedirs(target_dir)
            
        # Copy files
        print(f"Copying files from {source_include_path} to {target_dir}")
        count = 0
        for item in os.listdir(source_include_path):
            # Skip rte_base
            if item == "rte_base":
                print("Skipping rte_base")
                continue
                
            s = os.path.join(source_include_path, item)
            d = os.path.join(target_dir, item)
            
            if os.path.isdir(s):
                shutil.copytree(s, d)
            else:
                shutil.copy2(s, d)
            count += 1
            
        print(f"Successfully copied {count} items.")
        
    except Exception as e:
        print(f"An error occurred: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()
