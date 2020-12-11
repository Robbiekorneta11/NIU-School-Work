//
//  Book+CoreDataProperties.swift
//  Assignment6
//
//  Created by Robbie Korneta on 11/30/20.
//  Copyright © 2020 Robbie Korneta. All rights reserved.
//

import Foundation
import CoreData


extension Book {

    /*
     *  Get the information of a book to search for books
     *
     *  @return the result of the fetch for the books
     */
    @nonobjc public class func fetchRequest() -> NSFetchRequest<Book> {
        
        return NSFetchRequest<Book>(entityName: "Book")
        
    }

    @NSManaged public var author: String        // Author of the book
    @NSManaged public var title: String         // Title of the book
    @NSManaged public var releaseYear: String?  // Release year of the book

}
