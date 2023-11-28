import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;
import java.nio.file.*;

@RestController
public class ImageUploadController {

    @PostMapping("/upload")
    public String handleFileUpload(@RequestParam("file") MultipartFile file) {

        // Check if the file is coming from the correct page
    if (!"ASCII Generator SVG".equals(title)) {
        throw new IllegalArgumentException("File must be uploaded from the 'ASCII Generator SVG' page.");
    }

        // Save the file somewhere
        Path path = Paths.get("uploads/" + file.getOriginalFilename());
        try {
            Files.write(path, file.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }

        // Convert the image to ASCII art
        String asciiArt = convertImageToAsciiArt(path);

        // Return the ASCII art
        return asciiArt;
    }

    private String convertImageToAsciiArt(Path imagePath) {
        // This is where you would add your ASCII art generation code.
        // There are Java libraries available that can do this, or you could write your own.
        // Include the ascii-art library
var AsciiArt = require('ascii-art');

// Function to convert an image to ASCII art
function convertImageToAsciiArt(imagePath) {
    AsciiArt.image({
        filepath: imagePath,
        width: 100,
        alphabet:'variant1'
    }, function(err, rendered){
        console.log(rendered);
    });
}

// Function to handle file upload
function uploadFile() {
    var file = document.getElementById('myFile').files[0];

    // Check file size (must be less than 10MB)
    if (file.size > 10485760) {
        alert('File size must be less than 10MB.');
        return;
    }

    // Check image dimensions (must be less than 24000px square)
    var img = new Image();
    img.onload = function() {
        if (this.width > 24000 || this.height > 24000) {
            alert('Image dimensions must be less than 24000px square.');
            return;
        }

        // If all checks pass, upload the file
        var formData = new FormData();
        formData.append('file', file);

        fetch('/upload', {
            method: 'POST',
            body: formData
        }).then(response => {
            if (!response.ok) {
                throw new Error('Network response was not ok');
            }
            return response.text();
        }).then(data => {
            // Convert the uploaded image to ASCII art
            convertImageToAsciiArt(data);
        }).catch(error => {
            console.error('There was a problem with the file upload:', error);
        });
    };
    img.src = URL.createObjectURL(file);
}
        return "";
    }
}
// Server side upload handler and generator converter artist ASCII type
