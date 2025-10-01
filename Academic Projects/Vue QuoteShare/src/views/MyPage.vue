<template>
<div>
  <div v-if="user">
    <div class="myheader">
      <div>
        <h1>{{user.name}}</h1>
      </div>
      <div>
        <p>
          <a @click="toggleUpload"><i class="far fa-image"></i></a>
          <button @click="logout">Logout</button>
        </p>
      </div>
    </div>
  </div>
  <div v-else>
    <p>Please register for an account or login.</p>
    <router-link to="/register" class="button">Register</router-link> or
    <router-link to="/login" class="button">Login</router-link>
  </div>
</div>
</template>

<script>
import EscapeEvent from '@/components/EscapeEvent.vue'
import Uploader from '@/components/Uploader.vue'

export default {
  name: 'mypage',
  components: {
    EscapeEvent,
    Uploader,
  },
  data() {
    return {
      show: false,
    }
  },
  created() {
    this.$store.dispatch("getUser");
  },
  methods: {
    async logout() {
      try {
        this.error = await this.$store.dispatch("logout");
      } catch (error) {
        console.log(error);
      }
    },
    escape() {
      this.show = false;
    },
    toggleUpload() {
      this.show = true;
    },
    async created() {
      await this.$store.dispatch("getUser");
      await this.$store.dispatch("getMyPhotos");
    },
    async uploadFinished() {
      this.show = false;
      try {
        this.error = await this.$store.dispatch("getMyPhotos");
      } catch (error) {
        console.log(error);
      }
    },
  },
  computed: {
    photos() {
      return this.$store.state.photos;
    },
    user() {
      return this.$store.state.user;
    },
  },
}
</script>

<style scoped>
.header {
  display: flex;
}

.header a {
  padding-left: 50px;
  color: #222;
  font-size: 2em;
}

.header svg {
  margin-top: 12px;
}
</style>
