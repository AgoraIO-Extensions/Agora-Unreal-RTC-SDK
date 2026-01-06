import os
import sys
import json
import argparse

def get_dependencies(data, platform):
    deps = []
    # Case insensitive comparison for platform
    target_platform = platform.lower()
    for item in data:
        current_platform = item.get('platform', '').lower()
        if current_platform == target_platform:
            deps.extend(item.get('cdn', []))
    return deps

def is_video_sdk(url):
    url_lower = url.lower()
    return 'full' in url_lower or 'video' in url_lower

def is_audio_sdk(url):
    url_lower = url.lower()
    return 'voice' in url_lower or 'audio' in url_lower

def update_json_data(data, category, platform_key, url):
    if category not in data:
        data[category] = {}
    print(f"Updating .{category}.{platform_key} to: {url}")
    data[category][platform_key] = url

def main():
    parser = argparse.ArgumentParser(description='Update dependency URLs')
    parser.add_argument('json_input', help='JSON string containing dependencies')
    args = parser.parse_args()
    
    try:
        # Handle double-escaped JSON if needed
        json_str = args.json_input
        if json_str.startswith('"') and json_str.endswith('"'):
            # It might be a stringified JSON string
            try:
                # First decode: remove outer quotes and unescape
                json_str = json.loads(json_str)
            except:
                pass
                
        input_data = json.loads(json_str)
    except json.JSONDecodeError as e:
        print(f"Error decoding JSON: {e}")
        sys.exit(1)
        
    # Path setup
    script_dir = os.path.dirname(os.path.realpath(__file__))
    project_root = os.path.realpath(os.path.join(script_dir, '..', '..'))
    url_json_path = os.path.join(project_root, 'Agora-Unreal-SDK-CPP', 'AgoraPlugin', 'Resources', 'url.json')
    
    if not os.path.exists(url_json_path):
        print(f"Error: {url_json_path} not found")
        sys.exit(1)
        
    try:
        with open(url_json_path, 'r') as f:
            json_data = json.load(f)
            
        # Extract version
        version = None
        for item in input_data:
            v = item.get('version')
            if v:
                version = v
                break
        
        if version:
            print(f"Detected version: {version}")

        # Process Windows (Update both video and audio)
        win_deps = get_dependencies(input_data, 'Windows')
        for url in win_deps:
            update_json_data(json_data, 'video', 'native_win', url)
            update_json_data(json_data, 'audio', 'native_win', url)
            
        # Process Mac (Update both video and audio)
        mac_deps = get_dependencies(input_data, 'macOS')
        for url in mac_deps:
            update_json_data(json_data, 'video', 'native_mac', url)
            update_json_data(json_data, 'audio', 'native_mac', url)
            
        # Process Android (Distinguish video/audio)
        android_deps = get_dependencies(input_data, 'Android')
        for url in android_deps:
            if is_video_sdk(url):
                update_json_data(json_data, 'video', 'native_android', url)
            if is_audio_sdk(url):
                update_json_data(json_data, 'audio', 'native_android', url)
                
        # Process iOS (Distinguish video/audio)
        ios_deps = get_dependencies(input_data, 'iOS')
        for url in ios_deps:
            if is_video_sdk(url):
                update_json_data(json_data, 'video', 'native_ios', url)
            if is_audio_sdk(url):
                update_json_data(json_data, 'audio', 'native_ios', url)

        # Write changes
        with open(url_json_path, 'w') as f:
            json.dump(json_data, f, indent=2)
            
        print("Dependencies update completed successfully!")
        print(f"Updated url.json at: {url_json_path}")
        
    except Exception as e:
        print(f"Failed to process: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()
