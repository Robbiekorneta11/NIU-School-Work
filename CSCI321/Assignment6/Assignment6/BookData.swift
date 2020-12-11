//
//  BookData.swift
//  Assignment6
//
//  Created by Robbie Korneta on 11/30/20.
//  Copyright © 2020 Robbie Korneta. All rights reserved.
//

import Foundation

// Represents the data that is in a book
struct BookData: Decodable {
    
    let author: String          // Author of the book
    let title: String           // Title of the book
    let releaseYear: String     // Release year of the book
    
}
