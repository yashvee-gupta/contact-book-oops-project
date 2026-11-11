# Contact Book / Phone Directory (C++)

A simple OOP mini project in C++ that stores contacts (name and phone number) and runs in the terminal.

## Features
- Add a contact (duplicate names are not allowed)
- Delete a contact
- Search contacts by name (partial match works)
- Display all contacts in alphabetical order
- Contacts are saved to `contacts.txt` and loaded automatically on start
- Export the directory to `contacts.html`, styled with `style.css`

## OOP concepts used
- Classes and objects (`Contact`, `ContactBook`)
- Encapsulation (private data with public getters)
- Constructors
- Operator overloading (`operator<` for sorting)
- File streams (`ifstream`, `ofstream`)
- STL `vector` and `sort`


## Files
| File | Purpose |

| `main.cpp` | All the C++ code |

| `style.css` | Styling for the exported HTML page |

| `contacts.txt` | Saved contacts (created automatically) |

| `contacts.html` | Browser view (created on export) |
