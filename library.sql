-- Insert this with order from top to bottom


CREATE TABLE genres(
    genre_id int NOT NULL AUTO_INCREMENT PRIMARY KEY,
    genre  varchar(50) NOT NULL
);

CREATE TABLE authors(
    author_id int NOT NULL AUTO_INCREMENT PRIMARY KEY,
    name  varchar(100) NOT NULL
);

CREATE TABLE books(
    book_id int NOT NULL AUTO_INCREMENT PRIMARY KEY,
    title  varchar(100) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    genre_id int,
    author_id int,
    isBorrowed boolean NOT NULL DEFAULT FALSE,
    FOREIGN KEY (genre_id) REFERENCES genres(genre_id),
    FOREIGN KEY (author_id) REFERENCES authors(author_id)
); 


CREATE TABLE members(
    member_id int NOT NULL AUTO_INCREMENT PRIMARY KEY,
    name  varchar(100) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP 
);

CREATE TABLE borrowed_books(
    borrowedBooks_id int NOT NULL AUTO_INCREMENT PRIMARY KEY,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    book_id int,
    member_id int,
    isReturned boolean NOT NULL DEFAULT FALSE,
    FOREIGN KEY (book_id) REFERENCES books(book_id),
    FOREIGN KEY (member_id) REFERENCES members(member_id)
); 


-- This are genres witch will be shown in library
INSERT INTO genres(genre) VALUES("Fantasy"),("Science Fiction"),("Dystopian"),
("Action"),("Adventure"),("Mystery"),("Horror"),("Thriller"),
("Historical Fiction"),("Romance"),("Literary Fiction"),("Graphic Novel"),
("Short Story"),("Memoir"),("Authobigraphy"),("Biography"),
("Food & Drink"),("Art & Photography"),("Self-help"),("History"),("Travel"),
("True Crime"),("Crime-fiction"),("Humor"),("Essay"),("Guide/How-to"),
("Relgion & Spirituality"),("Humanties & Social Sciences"),
("Parenting & Families"),("Science & Technology"),("Drama"),("Poetry"),
("Academic & School"),("Classics");

