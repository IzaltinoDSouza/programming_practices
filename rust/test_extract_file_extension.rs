/*
	It's redo of my c++ implementation without think about.
	It's try to be close as possible, but without use pointers,
	
	NOTE : this use allocation, in future I need to try a version without allocation.
*/
fn extract_file_extension(filename: &str) -> String {
    if filename.len() == 0 {
        return String::new();
    }

    let chars: Vec<char> = filename.chars().collect();

    //get filename size
    let mut i = filename.len() - 1;

    //go back until find dot (.)
    while i != 0 {
        if chars[i] == '.' {
            break;
        }
        i -= 1;
    }
    //check if has not dot (.), and return empty extension
    if i == 0 {
        return String::new();
    }
    i += 1;

    //copy to extension
    let mut extension = String::new();
    while i < filename.len() {
        extension.push(chars[i]);
        i += 1;
    }
    extension
}
#[test]
fn test_extract_file_extension_extract_extension() {
    let extension = extract_file_extension("pixel_art.png");
    assert_eq!(extension, "png");
}
#[test]
fn test_extract_file_extension_no_extension() {
    let extension = extract_file_extension("virus");
    assert_eq!(extension, "");
}
#[test]
fn test_extract_file_extension_empty_filename() {
    let extension = extract_file_extension("");
    assert_eq!(extension, "");
}
