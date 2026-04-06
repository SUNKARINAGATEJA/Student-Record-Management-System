import json
import os

FILE_NAME = "students.json"

# Load data
def load_data():
    if os.path.exists(FILE_NAME):
        with open(FILE_NAME, "r") as file:
            return json.load(file)
    return []

# Save data
def save_data(data):
    with open(FILE_NAME, "w") as file:
        json.dump(data, file, indent=4)

# Add student
def add_student():
    data = load_data()
    roll = input("Enter Roll No: ")
    name = input("Enter Name: ")
    marks = input("Enter Marks: ")

    student = {"roll": roll, "name": name, "marks": marks}
    data.append(student)
    save_data(data)

    print("✅ Student added successfully!")

# View students
def view_students():
    data = load_data()
    if not data:
        print("No records found.")
        return

    print("\n--- Student List ---")
    for s in data:
        print(f"Roll: {s['roll']} | Name: {s['name']} | Marks: {s['marks']}")

# Search student
def search_student():
    roll = input("Enter Roll No to search: ")
    data = load_data()

    for s in data:
        if s["roll"] == roll:
            print("Found:", s)
            return

    print("❌ Student not found.")

# Delete student
def delete_student():
    roll = input("Enter Roll No to delete: ")
    data = load_data()

    new_data = [s for s in data if s["roll"] != roll]
    save_data(new_data)

    print("🗑 Student deleted (if existed).")

# Update student
def update_student():
    roll = input("Enter Roll No to update: ")
    data = load_data()

    for s in data:
        if s["roll"] == roll:
            s["name"] = input("Enter new name: ")
            s["marks"] = input("Enter new marks: ")
            save_data(data)
            print("✏ Updated successfully!")
            return

    print("❌ Student not found.")

# Main menu
def main():
    while True:
        print("\n==== Student Management System ====")
        print("1. Add Student")
        print("2. View Students")
        print("3. Search Student")
        print("4. Delete Student")
        print("5. Update Student")
        print("6. Exit")

        choice = input("Enter choice: ")

        if choice == "1":
            add_student()
        elif choice == "2":
            view_students()
        elif choice == "3":
            search_student()
        elif choice == "4":
            delete_student()
        elif choice == "5":
            update_student()
        elif choice == "6":
            print("Exiting...")
            break
        else:
            print("Invalid choice!")

if __name__ == "__main__":
    main()