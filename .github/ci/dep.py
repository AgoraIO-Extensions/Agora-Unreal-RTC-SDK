import os
import sys
import json
import argparse

def get_dependencies(data, platform):
    deps = []
    for item in data:
        if item.get('platform') == platform:
            deps.extend(item.get('cdn', []))
    return deps

def detect_release_type(all_deps):
    has_video = False
    has_audio = False
    
    for dep in all_deps:
        if 'Video' in dep:
            has_video = True
        if 'Audio' in dep or 'Voice' in dep:
            has_audio = True
            
    if has_video and not has_audio:
        return 'video'
    elif has_audio and not has_video:
        return 'audio'
    else:
        return 'video'

def update_url_json(json_path, release_type, platform_key, url):
    if not url:
        return
        
    if not os.path.exists(json_path):
        print(f"Error: {json_path} not found")
        sys.exit(1)
        
    try:
        with open(json_path, 'r') as f:
            data = json.load(f)
            
        if release_type not in data:
            data[release_type] = {}
            
        print(f"Updating .{release_type}.{platform_key} with value: {url}")
        data[release_type][platform_key] = url
        
        with open(json_path, 'w') as f:
            json.dump(data, f, indent=2)
            
        print(f"Successfully updated .{release_type}.{platform_key} to: {url}")
        
    except Exception as e:
        print(f"Failed to update json: {e}")
        sys.exit(1)

def main():
    parser = argparse.ArgumentParser(description='Update dependency URLs')
    parser.add_argument('json_input', help='JSON string containing dependencies')
    args = parser.parse_args()
    
    try:
        input_data = json.loads(args.json_input)
    except json.JSONDecodeError as e:
        print(f"Error decoding JSON: {e}")
        sys.exit(1)
        
    # Path setup
    # Script is in .github/ci/dep.py
    script_dir = os.path.dirname(os.path.realpath(__file__))
    # Project root is ../../ from .github/ci
    project_root = os.path.realpath(os.path.join(script_dir, '..', '..'))
    url_json_path = os.path.join(project_root, 'Agora-Unreal-SDK-CPP', 'AgoraPlugin', 'Resources', 'url.json')
    
    # Extract dependencies
    ios_deps = get_dependencies(input_data, 'iOS')
    mac_deps = get_dependencies(input_data, 'macOS')
    android_deps = get_dependencies(input_data, 'Android')
    win_deps = get_dependencies(input_data, 'Windows')
    
    # Extract version
    version = None
    for item in input_data:
        v = item.get('version')
        if v:
            version = v
            break
            
    if version:
        print(f"Detected version: {version}")
        
    # Detect release type
    all_deps = ios_deps + mac_deps + android_deps + win_deps
    release_type = detect_release_type(all_deps)
    print(f"Detected release type: {release_type}")
    
    # Update JSON
    # Helper to pick first native dep
    def get_first_dep(deps):
        return deps[0] if deps else None
        
    win_url = get_first_dep(win_deps)
    if win_url:
        print(f"Windows native dependency: {win_url}")
        update_url_json(url_json_path, release_type, 'native_win', win_url)
    else:
        print("No windows native dependencies need to change.")

    mac_url = get_first_dep(mac_deps)
    if mac_url:
        print(f"Mac native dependency: {mac_url}")
        update_url_json(url_json_path, release_type, 'native_mac', mac_url)
    else:
        print("No mac native dependencies need to change.")

    ios_url = get_first_dep(ios_deps)
    if ios_url:
        print(f"iOS native dependency: {ios_url}")
        update_url_json(url_json_path, release_type, 'native_ios', ios_url)
    else:
        print("No iOS native dependencies need to change.")

    android_url = get_first_dep(android_deps)
    if android_url:
        print(f"Android native dependency: {android_url}")
        update_url_json(url_json_path, release_type, 'native_android', android_url)
    else:
        print("No Android native dependencies need to change.")
        
    print("Dependencies update completed successfully!")
    print(f"Updated url.json at: {url_json_path}")

if __name__ == "__main__":
    main()

