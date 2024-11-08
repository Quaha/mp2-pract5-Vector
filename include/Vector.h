#pragma once

template <typename VectorType> class Vector {
private:

	VectorType* prev_vector = nullptr; // curr_capacity / 2
	VectorType* curr_vector = nullptr; // curr_capacity
	VectorType* next_vector = nullptr; // curr_capacity * 2

	int curr_capacity = 2;

	int prev_sz = 0;
	int curr_sz = 1; // there is a fake element in order to simplify the implementation
	int next_sz = 0;

	void destruct(Vector* vector) {
		delete[] vector->prev_vector;
		delete[] vector->curr_vector;
		delete[] vector->next_vector;
	}

	void construct(Vector* vector) {
		vector->prev_vector = new VectorType[1]();
		vector->curr_vector = new VectorType[2]();
		vector->next_vector = new VectorType[4]();

		vector->curr_sz = 1;
		vector->curr_capacity = 2;
		vector->prev_sz = 0;
		vector->next_sz = 0;
	}

public:

	Vector() {
		construct(this);
	}

	~Vector() {
		destruct(this);
	}

	Vector(const Vector& other) {
		this->curr_capacity = other.curr_capacity;

		this->prev_sz = other.prev_sz;
		this->curr_sz = other.curr_sz;
		this->next_sz = other.next_sz;

		this->prev_vector = new VectorType[prev_sz];
		this->curr_vector = new VectorType[curr_sz];
		this->next_vector = new VectorType[next_sz];

		for (int i = 0; i < prev_sz; ++i) {
			this->prev_vector[i] = other.prev_vector[i];
		}

		for (int i = 0; i < curr_sz; ++i) {
			this->curr_vector[i] = other.curr_vector[i];
		}

		for (int i = 0; i < next_sz; ++i) {
			this->next_vector[i] = other.next_vector[i];
		}
	}

	Vector(Vector&& other) {
		this->prev_vector = other.prev_vector;
		this->curr_vector = other.curr_vector;
		this->next_vector = other.next_vector;

		this->curr_capacity = other.curr_capacity;

		this->curr_sz = other.curr_sz;
		this->prev_sz = other.prev_sz;
		this->next_sz = other.next_sz;

		construct(&other);
	}

	Vector& operator=(const Vector& other) {
		if (this == &other) return *this;

		destruct(this);

		this->curr_capacity = other.curr_capacity;

		this->prev_sz = other.prev_sz;
		this->curr_sz = other.curr_sz;
		this->next_sz = other.next_sz;

		this->prev_vector = new VectorType[prev_sz];
		this->curr_vector = new VectorType[curr_sz];
		this->next_vector = new VectorType[next_sz];


		for (int i = 0; i < prev_sz; ++i) {
			this->prev_vector[i] = other.prev_vector[i];
		}

		for (int i = 0; i < curr_sz; ++i) {
			this->curr_vector[i] = other.curr_vector[i];
		}

		for (int i = 0; i < next_sz; ++i) {
			this->next_vector[i] = other.next_vector[i];
		}

		return *this;
	}

	Vector& operator=(Vector&& other) {
		if (this == &other) return *this;

		destruct(this);

		this->prev_vector = other.prev_vector;
		this->curr_vector = other.curr_vector;
		this->next_vector = other.next_vector;

		this->curr_capacity = other.curr_capacity;

		this->curr_sz = other.curr_sz;
		this->prev_sz = other.prev_sz;
		this->next_sz = other.next_sz;

		construct(&other);

		return *this;
	}

	void push_back(const VectorType& value) {
		curr_vector[curr_sz] = value;
		++curr_sz;

		if (prev_sz == 0) {
			next_vector[next_sz] = curr_vector[next_sz];
			next_vector[next_sz + 1] = curr_vector[next_sz + 1];
			next_sz += 2;
		}
		else {
			--prev_sz;
		}


		if (curr_sz == curr_capacity) {
			delete[] prev_vector;

			prev_vector = curr_vector;
			curr_vector = next_vector;

			curr_capacity *= 2;
			next_vector = new VectorType[curr_capacity * 2];

			prev_sz = 0;
			next_sz = 0;
		}
	}

	void pop_back() {
		if (empty()) {
			throw std::out_of_range("It is forbidden to use the method .pop_back() on an empty vector!");
		}

		--curr_sz;

		if (next_sz != 0) {
			next_sz -= 2;
		}
		else {
			prev_vector[prev_sz] = curr_vector[prev_sz];
			++prev_sz;
		}

		if (curr_sz == curr_capacity / 4) {
			delete[] next_vector;

			next_vector = curr_vector;
			curr_vector = prev_vector;

			curr_capacity /= 2;

			prev_vector = new VectorType[curr_capacity / 2];

			prev_sz = 0;
			next_sz = 0;
		}
	}

	VectorType back() const {
		if (empty()) {
			throw std::out_of_range("It is forbidden to use the method .back() on an empty vector!");
		}
		return curr_vector[curr_sz - 1];
	}

	size_t size() const {
		return curr_sz - 1;
	}

	bool empty() const {
		return curr_sz == 1;
	}
};